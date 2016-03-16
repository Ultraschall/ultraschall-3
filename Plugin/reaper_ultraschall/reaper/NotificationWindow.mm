////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#import "NotificationWindow.h"
#import <WebKit/WebKit.h>

@implementation NotificationPanel

+ (void) showWithMessage:(NSString*)message asError:(BOOL)error
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle: @"Dismiss"];
    [alert setMessageText: message];
    [alert setAlertStyle: (error == YES) ? NSCriticalAlertStyle : NSInformationalAlertStyle];
    [alert beginSheetModalForWindow:[[NSApplication sharedApplication] mainWindow] completionHandler:nil];
}

+ (void) showWithMessage:(NSString*)message info:(NSString*)info asError:(BOOL)error
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle: @"Dismiss"];
    [alert setMessageText: message];
    [alert setInformativeText: info];
    [alert setAlertStyle: (error == YES) ? NSCriticalAlertStyle : NSInformationalAlertStyle];
    [alert beginSheetModalForWindow:[[NSApplication sharedApplication] mainWindow] completionHandler:nil];
}

+ (void) showUpdateMessage:(NSString*)message info:(NSString*)info changeLog:(NSString *)changeLog
{
    // Be sure to run dialog on the main thread
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        WebView* webView = [[WebView alloc] initWithFrame:NSMakeRect(0,0,400,300)];
        [[webView mainFrame] loadHTMLString:changeLog baseURL:[NSURL URLWithString:@"http://ultraschall.fm/"]];
        [webView setFrameLoadDelegate:self];
        NSAlert *alert = [[NSAlert alloc] init];
        [alert addButtonWithTitle: @"Dismiss"];
        [alert setMessageText: message];
        [alert setInformativeText: info];
        [alert setAccessoryView:webView];
        [alert setAlertStyle: NSInformationalAlertStyle];
        [alert beginSheetModalForWindow:[[NSApplication sharedApplication] mainWindow] completionHandler:nil];

    }];
}

+ (void)webView:(WebView *)sender didStartProvisionalLoadForFrame:(WebFrame *)frame {
    NSString* url = sender.mainFrameURL;
    [sender stopLoading:nil];
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:url]];
}


@end
