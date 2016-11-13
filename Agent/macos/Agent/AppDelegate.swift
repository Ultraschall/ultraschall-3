////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate, NSTableViewDataSource, NSTableViewDelegate, XMLParserDelegate {

   @IBOutlet weak var window: NSWindow!
   @IBOutlet weak var updateLabel: NSTextField!
   @IBOutlet weak var tableView: NSTableView!
   
   var cellText : String = "cellText"
   
   func applicationDidFinishLaunching(_ aNotification: Notification) {
      tableView.dataSource = self
      
      tableView.tableColumns[0].width = 250;
      tableView.tableColumns[0].headerCell.title = "Component"
      
      tableView.tableColumns[1].width = 100;
      tableView.tableColumns[1].headerCell.title = "Version"

      tableView.tableColumns[2].width = 400;
      tableView.tableColumns[2].headerCell.title = "Location"
      
      tableView.reloadData()
      
      startUpdateCheck()
   }

   func applicationWillTerminate(_ aNotification: Notification) {
      // Insert code here to tear down your application
   }

   func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
      return true;
   }
   
   func numberOfRows(in tableView: NSTableView) -> Int {
      return 7
   }
   
   func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any? {
      return "test"
   }
   
   func showUpdateCheckResult(updateAvailable: Bool) {
      updateLabel.alignment = .center
      
      if updateAvailable == true {
         updateLabel.stringValue = "ULTRASCHALL is outdated! Download the latest version from ultraschall.fm!"
      }
      else {
         updateLabel.stringValue = "Congratulations! You are using the most current version."
      }

      /*
      let stringHeight: CGFloat = updateLabel.attributedStringValue.size().height
      let frame = updateLabel.frame
      var titleRect:  NSRect = updateLabel.cell!.titleRect(forBounds: frame)
      
      titleRect.size.height = stringHeight + ( stringHeight - (updateLabel.font!.ascender + updateLabel.font!.descender ) )
      titleRect.origin.y = frame.size.height / 2  - updateLabel.lastBaselineOffsetFromBottom - updateLabel.font!.xHeight / 2
      updateLabel.frame = titleRect
      */
   }
   
   func startUpdateCheck() {
      DispatchQueue.global().async {
         if let xml : String = try? String(contentsOf: URL(string: "https://ultraschall.io/ultraschall_release.xml")!) {
            if let data : Data = xml.replacingOccurrences(of: "'", with: "&quot;").data(using: String.Encoding.utf8){
               let parser : XMLParser = XMLParser(data: data)
               parser.delegate = self
               parser.parse()
            }
         }
      }
   }
   
   public func parser(_ parser: XMLParser, didStartElement elementName: String, namespaceURI: String?, qualifiedName qName: String?, attributes attributeDict: [String : String] = [:]) {
      var updateAvailable : Bool = false
      if elementName == "enclosure" {
         if let remoteString : String = attributeDict["sparkle:version"] {
            let remoteStringTokens : [String] = remoteString.components(separatedBy: ".")
            if remoteStringTokens.count == 4 {
               let localStringTokens : [String] = "3.0.0.0".components(separatedBy: ".")
               for (i, localStringToken) in localStringTokens.enumerated() {
                  let remoteStringToken : String = remoteStringTokens[i]
                  if localStringToken < remoteStringToken {
                     updateAvailable = true
                     break
                  }
                  else if localStringToken > remoteStringToken {
                     updateAvailable = false
                     break
                  }
                  else {
                     continue
                  }
               }
            }
         }
      }

      DispatchQueue.main.async {
         self.showUpdateCheckResult(updateAvailable: updateAvailable)
      }
   }
}

