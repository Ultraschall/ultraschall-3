/* Cockos SWELL (Simple/Small Win32 Emulation Layer for Losers (who use OS X))
   Copyright (C) 2006-2007, Cockos, Inc.

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
  

    This file provides basic windows menu API to interface an NSMenu

  */

#ifndef SWELL_PROVIDED_BY_APP

#import <Cocoa/Cocoa.h>

#include "swell.h"
#include "swell-menugen.h"

#include "swell-internal.h"




bool SetMenuItemText(HMENU hMenu, int idx, int flag, const char *text)
{
  NSMenu *menu=(NSMenu *)hMenu;
  
  NSMenuItem *item;
  if (flag & MF_BYPOSITION) item=[menu itemAtIndex:idx];
  else item =[menu itemWithTag:idx];
  if (!item) 
  {
    if (!(flag & MF_BYPOSITION))
    {
      int x;
      int n=[menu numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[menu itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m=[item submenu];
          if (m && SetMenuItemText(m,idx,flag,text)) return true;
        }
      }
    }
    return false;
  }
  NSString *label=(NSString *)SWELL_CStringToCFString(text); 
  
  [item setTitle:label];
  if ([item hasSubmenu] && [item submenu]) [[item submenu] setTitle:label];

  [label release];
  return true;
}

bool EnableMenuItem(HMENU hMenu, int idx, int en)
{
  NSMenu *menu=(NSMenu *)hMenu;
  
  NSMenuItem *item;
  if (en & MF_BYPOSITION) item=[menu itemAtIndex:idx];
  else item =[menu itemWithTag:idx];
  if (!item) 
  {
    if (!(en & MF_BYPOSITION))
    {
      int x;
      int n=[menu numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[menu itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m=[item submenu];
          if (m && EnableMenuItem(m,idx,en)) return true;
        }
      }
    }
    return false;
  }
  [item setEnabled:((en&MF_GRAYED)?NO:YES)];
  return true;
}

bool CheckMenuItem(HMENU hMenu, int idx, int chk)
{
  NSMenu *menu=(NSMenu *)hMenu;
  if (!menu) return false;
  
  NSMenuItem *item;
  if (chk & MF_BYPOSITION) item=[menu itemAtIndex:idx];
  else item =[menu itemWithTag:idx];
  if (!item) 
  {
    if (!(chk & MF_BYPOSITION))
    {
      int x;
      int n=[menu numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[menu itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m=[item submenu];
          if (m && CheckMenuItem(m,idx,chk)) return true;
        }
      }
    }
    return false;  
  }
  [item setState:((chk&MF_CHECKED)?NSOnState:NSOffState)];
  
  return true;
}
HMENU SWELL_GetCurrentMenu()
{
  return [NSApp mainMenu];
}
void SWELL_SetCurrentMenu(HMENU hmenu)
{
  if (hmenu && [(id)hmenu isKindOfClass:[NSMenu class]])
  {
    [NSApp setMainMenu:(NSMenu *)hmenu];
  }
}

HMENU GetSubMenu(HMENU hMenu, int pos)
{
  NSMenu *menu=(NSMenu *)hMenu;
  
  NSMenuItem *item=menu && pos >=0 && pos < [menu numberOfItems] ? [menu itemAtIndex:pos] : 0; 
  if (item && [item hasSubmenu]) return [item submenu];
  return 0;
}

int GetMenuItemCount(HMENU hMenu)
{
  NSMenu *menu=(NSMenu *)hMenu;
  return [menu numberOfItems];
}

int GetMenuItemID(HMENU hMenu, int pos)
{
  NSMenu *menu=(NSMenu *)hMenu;
  if (pos < 0 || pos >= [menu numberOfItems]) return 0;
  
  NSMenuItem *item=[menu itemAtIndex:pos]; 
  if (item) 
  {
    if ([item hasSubmenu]) return -1;
    return [item tag];
  }
  return 0;
}

bool SetMenuItemModifier(HMENU hMenu, int idx, int flag, int code, unsigned int mask)
{

#if 0 // enable this once we make SWELL_KeyToASCII decent
  int n2=0;
  int n1 = SWELL_KeyToASCII(code,flag,&n2);
  if (n1)
  {
    code=n1;
    flag=n2;
  }
#endif
  
  NSMenu *menu=(NSMenu *)hMenu;
  
  NSMenuItem *item;
  if (flag & MF_BYPOSITION) item=[menu itemAtIndex:idx];
  else item =[menu itemWithTag:idx];
  if (!item) 
  {
    if (!(flag & MF_BYPOSITION))
    {
      int x;
      int n=[menu numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[menu itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m=[item submenu];
          if (m && SetMenuItemModifier(m,idx,flag,code,mask)) return true;
        }
      }
    }
    return false;
  }
  
  bool suppressShift = false;
  unichar arrowKey = 0;
  int codelow = code&127;
  if ((code>='A' && code <='Z') ||
      (code>='0' && code <= '9') ||   
      ( !(flag&FVIRTKEY) && ( 
         codelow == '\'' ||
         codelow == '"' || 
         codelow == ',' ||
         codelow == '.' || 
         codelow == '!' ||
         codelow == '[' || codelow == ']'
         )))      
  {
    arrowKey=codelow;
    if (!(mask & FSHIFT) && arrowKey < 256) arrowKey=tolower(arrowKey);
    
    if (code>='A' && code<='Z') suppressShift=true;
  }
  else if (code >= VK_F1 && code <= VK_F12)
  {
    arrowKey = NSF1FunctionKey + code - VK_F1;
  }
  else switch (code&0xff)
  {
    #define DEFKP(wink,mack) case wink: arrowKey = mack; break;
    DEFKP(VK_UP,NSUpArrowFunctionKey)
    DEFKP(VK_DOWN,NSDownArrowFunctionKey)
    DEFKP(VK_LEFT,NSLeftArrowFunctionKey)
    DEFKP(VK_RIGHT,NSRightArrowFunctionKey)
    DEFKP(VK_INSERT,NSInsertFunctionKey)
    DEFKP(VK_DELETE,NSDeleteFunctionKey)
    DEFKP(VK_HOME,NSHomeFunctionKey)
    DEFKP(VK_END,NSEndFunctionKey)
    DEFKP(VK_NEXT,NSPageDownFunctionKey)
    DEFKP(VK_PRIOR,NSPageUpFunctionKey)
    DEFKP(VK_SUBTRACT,'-')
  }
   
  unsigned int mask2=0;
  if (mask&FALT) mask2|=NSAlternateKeyMask;
  if (!suppressShift) if (mask&FSHIFT) mask2|=NSShiftKeyMask;
  if (mask&FCONTROL) mask2|=NSCommandKeyMask;
     
  [item setKeyEquivalentModifierMask:mask2];
  [item setKeyEquivalent:arrowKey?[NSString stringWithCharacters:&arrowKey length:1]:@""];
  return true;
}

static void __filtnametobuf(char *out, const char *in, int outsz)
{
  while (*in && outsz>1)
  {
    if (*in == '\t') break;
    if (*in == '&')
    {
      in++;
    }
    *out++=*in++;
    outsz--;
  }
  *out=0;
}

// #define SWELL_MENU_ACCOUNTING

#ifdef SWELL_MENU_ACCOUNTING
struct menuTmp
{
  NSMenu *menu;
  NSString *lbl;
};

WDL_PtrList<menuTmp> allMenus;
#endif

@implementation SWELL_Menu
- (id)copyWithZone:(NSZone *)zone
{
  id rv = [super copyWithZone:zone];
#ifdef SWELL_MENU_ACCOUNTING
  if (rv)
  {
    menuTmp *mt = new menuTmp;
    mt->menu=(NSMenu *)rv;
    NSString *lbl = [(SWELL_Menu *)rv title];
    mt->lbl = lbl;
    [lbl retain];
    allMenus.Add(mt);
    NSLog(@"copy menu, new count=%d lbl=%@\n",allMenus.GetSize(),lbl);
  }
#endif
  return rv;
}
-(void)dealloc
{
#ifdef SWELL_MENU_ACCOUNTING
  int x;
  bool f=false;
  for(x=0;x<allMenus.GetSize();x++)
  {
    if (allMenus.Get(x)->menu == self)
    {
      NSLog(@"dealloc menu, found self %@\n",allMenus.Get(x)->lbl);
      allMenus.Delete(x);
      f=true;
      break;
    }
  }

  NSLog(@"dealloc menu, new count=%d %@\n",allMenus.GetSize(), [self title]);
  if (!f) 
  {
    NSLog(@"deleting unfound menu!!\n");
  }
#endif
  [super dealloc];
}
@end

HMENU CreatePopupMenu()
{
  return CreatePopupMenuEx(NULL);
}
HMENU CreatePopupMenuEx(const char *title)
{
  SWELL_Menu *m;
  if (title)
  {
    char buf[1024];
    __filtnametobuf(buf,title,sizeof(buf));
    NSString *lbl=(NSString *)SWELL_CStringToCFString(buf);
    m=[[SWELL_Menu alloc] initWithTitle:lbl];
#ifdef SWELL_MENU_ACCOUNTING
    menuTmp *mt = new menuTmp;
    mt->menu=m;
    mt->lbl = lbl;
    [lbl retain];
    allMenus.Add(mt);
    NSLog(@"alloc menu, new count=%d lbl=%@\n",allMenus.GetSize(),lbl);
#endif
    [lbl release];
  }
  else
  {
    m=[[SWELL_Menu alloc] init];
#ifdef SWELL_MENU_ACCOUNTING
    menuTmp *mt = new menuTmp;
    mt->menu=m;
    mt->lbl = @"<none>";
    allMenus.Add(mt);
    NSLog(@"alloc menu, new count=%d lbl=%@\n",allMenus.GetSize(),@"<none>");
#endif
  }
  [m setAutoenablesItems:NO];

  return (HMENU)m;
}

void DestroyMenu(HMENU hMenu)
{
  if (hMenu)
  {
    NSMenu *m=(NSMenu *)hMenu;
    [m release];
  }
}



int AddMenuItem(HMENU hMenu, int pos, const char *name, int tagid)
{
  if (!hMenu) return -1;
  NSMenu *m=(NSMenu *)hMenu;
  NSString *label=(NSString *)SWELL_CStringToCFString(name); 
  NSMenuItem *item=[m insertItemWithTitle:label action:NULL keyEquivalent:@"" atIndex:pos];
  [label release];
  [item setTag:tagid];
  [item setEnabled:YES];
  return 0;
}

bool DeleteMenu(HMENU hMenu, int idx, int flag)
{
  if (!hMenu) return false;
  NSMenu *m=(NSMenu *)hMenu;
  NSMenuItem *item=NULL;
  
  if (flag&MF_BYPOSITION)
  {
    if (idx >=0 && idx < [m numberOfItems])
      item=[m itemAtIndex:idx];
  }
  else
  {
    item=[m itemWithTag:idx];
  }
  if (!item) return false;
  
  if ([item hasSubmenu])
  {
    [m setSubmenu:nil forItem:item];
  }
  [m removeItem:item];
  return true;
}


BOOL SetMenuItemInfo(HMENU hMenu, int pos, BOOL byPos, MENUITEMINFO *mi)
{
  if (!hMenu) return 0;
  NSMenu *m=(NSMenu *)hMenu;
  NSMenuItem *item;
  if (byPos) item=[m itemAtIndex:pos];
  else item=[m itemWithTag:pos];

  if (!item) 
  {
    if (!byPos)
    {
      int x;
      int n=[m numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[m itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m1=[item submenu];
          if (m1 && SetMenuItemInfo(m1,pos,byPos,mi)) return true;
        }
      }      
    }
    return 0;
  }
  
  if ((mi->fMask & MIIM_SUBMENU) && mi->hSubMenu) // do this before MIIM_TYPE so we title the submenu properly
  {  
    [m setSubmenu:(NSMenu*)mi->hSubMenu forItem:item];
    [((NSMenu*)mi->hSubMenu) release]; // let the parent menu free it
  } 
  if (mi->fMask & MIIM_TYPE)
  {
    if (mi->fType == MFT_STRING && mi->dwTypeData)
    {
      char buf[1024];
      __filtnametobuf(buf,mi->dwTypeData?mi->dwTypeData:"(null)",sizeof(buf));
      NSString *label=(NSString *)SWELL_CStringToCFString(buf); 
      
      [item setTitle:label];
      if ([item hasSubmenu] && [item submenu]) [[item submenu] setTitle:label];
      
      [label release];      
    }
  }
  if (mi->fMask & MIIM_STATE)
  {
    [item setState:((mi->fState&MFS_CHECKED)?NSOnState:NSOffState)];
    [item setEnabled:((mi->fState&MFS_GRAYED)?NO:YES)];
  }
  if (mi->fMask & MIIM_ID)
  {
    [item setTag:mi->wID];
  }
  if (mi->fMask & MIIM_DATA)
  {
    SWELL_DataHold* newh = [[SWELL_DataHold alloc] initWithVal:(void*)mi->dwItemData];
    [item setRepresentedObject:newh]; 
    [newh release];    
  }
  
  return true;
}

BOOL GetMenuItemInfo(HMENU hMenu, int pos, BOOL byPos, MENUITEMINFO *mi)
{
  if (!hMenu) return 0;
  NSMenu *m=(NSMenu *)hMenu;
  NSMenuItem *item;
  if (byPos)
  {
    item=[m itemAtIndex:pos];
  }
  else item=[m itemWithTag:pos];
  
  if (!item) 
  {
    if (!byPos)
    {
      int x;
      int n=[m numberOfItems];
      for (x = 0; x < n; x ++)
      {
        item=[m itemAtIndex:x];
        if (item && [item hasSubmenu])
        {
          NSMenu *m1=[item submenu];
          if (m1 && GetMenuItemInfo(m1,pos,byPos,mi)) return true;
        }
      }      
    }
    return 0;
  }
  
  if (mi->fMask & MIIM_TYPE)
  {
    if ([item isSeparatorItem]) mi->fType = MFT_SEPARATOR;
    else
    {
      mi->fType = MFT_STRING;
      if (mi->dwTypeData && mi->cch)
      {
        mi->dwTypeData[0]=0;
        SWELL_CFStringToCString([item title], (char *)mi->dwTypeData, mi->cch);
      }
    }
  }
  
  if (mi->fMask & MIIM_DATA)
  {
    SWELL_DataHold *h=[item representedObject];
    mi->dwItemData =  (INT_PTR)(h && [h isKindOfClass:[SWELL_DataHold class]]? [h getValue] : 0);
  }
  
  if (mi->fMask & MIIM_STATE)
  {
    mi->fState=0;
    if ([item state]) mi->fState|=MFS_CHECKED;
    if (![item isEnabled]) mi->fState|=MFS_GRAYED;
  }
  
  if (mi->fMask & MIIM_ID)
  {
    mi->wID = [item tag];
  }
  
  if(mi->fMask && MIIM_SUBMENU)
  {
    if ([item hasSubmenu])
    {
      mi->hSubMenu = (HMENU)[item submenu];
    }
  }
  
  return 1;
  
}

void SWELL_InsertMenu(HMENU menu, int pos, int flag, int idx, const char *str)
{
  MENUITEMINFO mi={sizeof(mi),MIIM_ID|MIIM_STATE|MIIM_TYPE,MFT_STRING,
    (flag & ~MF_BYPOSITION),idx,NULL,NULL,NULL,0,(char *)str};
  InsertMenuItem(menu,pos,(flag&MF_BYPOSITION) ?  TRUE : FALSE, &mi);
}


void InsertMenuItem(HMENU hMenu, int pos, BOOL byPos, MENUITEMINFO *mi)
{
  if (!hMenu) return;
  NSMenu *m=(NSMenu *)hMenu;
  NSMenuItem *item;
  int ni=[m numberOfItems];
  
  if (!byPos) 
  {
    pos = [m indexOfItemWithTag:pos];
  }
  if (pos < 0 || pos > ni) pos=ni; 
  
  NSString *label=0;
  if (mi->fType == MFT_STRING)
  {
    char buf[1024];
    __filtnametobuf(buf,mi->dwTypeData?mi->dwTypeData:"(null)",sizeof(buf));
    label=(NSString *)SWELL_CStringToCFString(buf); 
    item=[m insertItemWithTitle:label action:NULL keyEquivalent:@"" atIndex:pos];
  }
  else if (mi->fType == MFT_BITMAP)
  {
    item=[m insertItemWithTitle:@"(no image)" action:NULL keyEquivalent:@"" atIndex:pos];
    if (mi->dwTypeData)
    {
      NSImage *i=(NSImage *)GetNSImageFromHICON(mi->dwTypeData);
      if (i)
      {
        [item setImage:i];
        [item setTitle:@""];
      }
    }
  }
  else
  {
    item = [NSMenuItem separatorItem];
    [m insertItem:item atIndex:pos];
  }
  
  if ((mi->fMask & MIIM_SUBMENU) && mi->hSubMenu)
  {
    if (label) [(NSMenu *)mi->hSubMenu setTitle:label];
    [m setSubmenu:(NSMenu *)mi->hSubMenu forItem:item];
    [((NSMenu *)mi->hSubMenu) release]; // let the parent menu free it
  }
  if (label) [label release];
  
  if (!ni) [m setAutoenablesItems:NO];
  [item setEnabled:YES];
  
  if (mi->fMask & MIIM_STATE)
  {
    if (mi->fState&MFS_GRAYED)
    {
      [item setEnabled:NO];
    }
    if (mi->fState&MFS_CHECKED)
    {
      [item setState:NSOnState];
    }
  }
 
   if (mi->fMask & MIIM_DATA)
  {
    SWELL_DataHold *h=[[SWELL_DataHold alloc] initWithVal:(void*)mi->dwItemData];
    [item setRepresentedObject:h];
    [h release];
  }
  else
  {
    [item setRepresentedObject:nil];
  }
 
  if (mi->fMask & MIIM_ID)
  {
    [item setTag:mi->wID];
  }
  
  NSMenuItem *fi=[m itemAtIndex:0];
  if (fi && fi != item)
  {
    if ([fi action]) [item setAction:[fi action]]; 
    if ([fi target]) [item setTarget:[fi target]]; 
  }
}



@implementation SWELL_PopupMenuRecv
-(id) initWithWnd:(HWND)wnd
{
  if ((self = [super init]))
  {
    cbwnd=wnd;
    m_act=0;
  }
  return self;
}

-(void) onSwellCommand:(id)sender
{
  int tag=[sender tag];
  if (tag)
    m_act=tag;
}

-(int) isCommand
{
  return m_act;
}

- (void)menuNeedsUpdate:(NSMenu *)menu
{
  if (cbwnd)
  {
    SendMessage(cbwnd,WM_INITMENUPOPUP,(WPARAM)menu,0);
    SWELL_SetMenuDestination((HMENU)menu,(HWND)self);
  }
}

@end

void SWELL_SetMenuDestination(HMENU menu, HWND hwnd)
{
  if (!menu || (hwnd && ![(id)hwnd respondsToSelector:@selector(onSwellCommand:)])) return;
  
  NSMenu *m=(NSMenu *)menu;
  [m setDelegate:(id)hwnd];
  int x,n=[m numberOfItems];
  for (x = 0; x < n; x++)
  {
    NSMenuItem *item=[m itemAtIndex:x];
    if (item)
    {
      if ([item hasSubmenu])
      {
        NSMenu *mm=[item submenu];
        if (mm) SWELL_SetMenuDestination((HMENU)mm,hwnd);
      }
      else
      {
        if ([item tag])
        {
          [item setTarget:(id)hwnd];
          if (hwnd) [item setAction:@selector(onSwellCommand:)];
        }
      }
    }
  }
}

int TrackPopupMenu(HMENU hMenu, int flags, int xpos, int ypos, int resvd, HWND hwnd, const RECT *r)
{
  if (hMenu)
  {
    NSMenu *m=(NSMenu *)hMenu;
    NSView *v=(NSView *)hwnd;
    if (v && [v isKindOfClass:[NSWindow class]]) v=[(NSWindow *)v contentView];
    if (!v) v=[[NSApp mainWindow] contentView];
    if (!v) return 0;
    
    SWELL_PopupMenuRecv *recv = [[SWELL_PopupMenuRecv alloc] initWithWnd:((flags&TPM_NONOTIFY)?0:hwnd)];
    
    SWELL_SetMenuDestination((HMENU)m,(HWND)recv);
    
    if (!(flags&TPM_NONOTIFY)&&hwnd)
    {
      SendMessage(hwnd,WM_INITMENUPOPUP,(WPARAM)m,0);
      SWELL_SetMenuDestination((HMENU)m,(HWND)recv);
    }
    
    NSEvent *event = [NSApp currentEvent];
    
    int etype = [event type];
#if 1 // disable this if you wish to have xpos/ypos be always used (someday we should enable it, yeah)
    if ((etype >= NSLeftMouseDown && etype <= NSMouseExited)||(etype >= NSOtherMouseDown && etype <= NSOtherMouseDragged))
    {
      
    }
    else  
#endif
    {
      // not mouse event! create a new event at these coordinates, faking it
      NSWindow *w = [v window];
      NSPoint pt = [w convertScreenToBase:NSMakePoint(xpos,ypos)];
      event = [NSEvent otherEventWithType:NSApplicationDefined location:pt modifierFlags:0 timestamp:[event timestamp] windowNumber:[w windowNumber] context:[w graphicsContext] subtype:0 data1:0 data2:0];

      //      event = [NSEvent mouseEventWithType:NSMouseMoved location:pt modifierFlags:0 timestamp:[event timestamp] windowNumber:[w windowNumber] context:[w graphicsContext] eventNumber:0 clickCount:0 pressure:0.0];
    }
    [NSMenu popUpContextMenu:m withEvent:event forView:v];

    int ret=[recv isCommand];
    
    SWELL_SetMenuDestination((HMENU)m,(HWND)NULL);
    [recv release];
    
    if (!(flags & TPM_NONOTIFY) && ret>0 && hwnd)
    {
      SendMessage(hwnd,WM_COMMAND,ret,0);
    }
    
    return ret;
  }
  return 0;
}




void SWELL_Menu_AddMenuItem(HMENU hMenu, const char *name, int idx, int flags)
{
  MENUITEMINFO mi={sizeof(mi),MIIM_ID|MIIM_STATE|MIIM_TYPE,MFT_STRING,
    (flags)?MFS_GRAYED:0,idx,NULL,NULL,NULL,0,(char *)name};
  if (!name)
  {
    mi.fType = MFT_SEPARATOR;
    mi.fMask&=~(MIIM_STATE|MIIM_ID);
  }
  InsertMenuItem(hMenu,GetMenuItemCount(hMenu),TRUE,&mi);
}


SWELL_MenuResourceIndex *SWELL_curmodule_menuresource_head; // todo: move to per-module thingy

static SWELL_MenuResourceIndex *resById(SWELL_MenuResourceIndex *head, int resid)
{
  SWELL_MenuResourceIndex *p=head;
  while (p)
  {
    if (p->resid == resid) return p;
    p=p->_next;
  }
  return 0;
}

HMENU SWELL_LoadMenu(SWELL_MenuResourceIndex *head, int resid)
{
  SWELL_MenuResourceIndex *p;
  
  if (!(p=resById(head,resid))) return 0;
  HMENU hMenu=CreatePopupMenu();
  if (hMenu) p->createFunc(hMenu);
  return hMenu;
}

HMENU SWELL_DuplicateMenu(HMENU menu)
{
  if (!menu) return 0;
  NSMenu *ret = (NSMenu *)[(NSMenu *)menu copy];
  return (HMENU)ret;
}

BOOL  SetMenu(HWND hwnd, HMENU menu)
{
  if (!hwnd||![(id)hwnd respondsToSelector:@selector(swellSetMenu:)]) return FALSE;
  
  SWELL_SetMenuDestination(menu,hwnd);

  [(id)hwnd swellSetMenu:(HMENU)menu];
  NSWindow *nswnd = (NSWindow *)hwnd;
  if ([nswnd isKindOfClass:[NSWindow class]] || 
     ([nswnd isKindOfClass:[NSView class]] && (nswnd=[(NSView *)nswnd window]) && hwnd == (HWND)[nswnd contentView]))
  {
    if ([NSApp keyWindow]==nswnd &&
        [NSApp mainMenu] != (NSMenu *)menu)
    {
      [NSApp setMainMenu:(NSMenu *)menu];
      SendMessage(hwnd,WM_INITMENUPOPUP,(WPARAM)menu,0); // find a better place for this! TODO !!!
    }
  }
  
  return TRUE;
}

HMENU GetMenu(HWND hwnd)
{
  if (!hwnd) return 0;
  
  HMENU ret = NULL;
  if (![(id)hwnd respondsToSelector:@selector(swellGetMenu)] || !(ret=(HMENU) [(id)hwnd swellGetMenu])) 
  {
    if ([(id)hwnd isKindOfClass:[NSView class]])
      hwnd = (HWND)[[(NSView *)hwnd window] contentView];
    else if ([(id)hwnd isKindOfClass:[NSWindow class]])
      hwnd = (HWND)[(NSWindow *)hwnd contentView];
  }
  if (!ret && hwnd && [(id)hwnd respondsToSelector:@selector(swellGetMenu)]) ret=(HMENU) [(id)hwnd swellGetMenu];
  return ret;
  
}



#endif
