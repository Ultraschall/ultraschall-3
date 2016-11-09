using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Xml;

namespace Ultraschall {
   class UpdateStatus {
      private bool updateRequired_ = false;
      public bool UpdateRequired {
         get {
            return updateRequired_;
         }
      }

      public UpdateStatus() {
         Refresh();
      }

      private static String QueryLocalVersion() {
         String localVersion = "3.0.0.0";
         return localVersion;
      }

      private static HttpWebRequest CreateRequest(String url) {
         HttpWebRequest request = null;

         request = (HttpWebRequest)WebRequest.Create(url);
         request.KeepAlive = false;
         DateTime buildDate = System.IO.File.GetLastWriteTime(System.Reflection.Assembly.GetExecutingAssembly().Location);
         request.UserAgent = @"UltraschallAgent " + QueryLocalVersion() + ", " + 
                             buildDate.ToUniversalTime().ToString("yyyy'-'MM'-'dd'T'HH':'mm':'ss'.'fff'Z'");
         ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12; // this is crucial, don't ask

         IWebProxy proxy = request.Proxy;
         if(proxy != null) {
            String proxyUri = proxy.GetProxy(request.RequestUri).ToString();
            if(String.IsNullOrEmpty(proxyUri) == false) {
               if(proxyUri != url) {
                  request.UseDefaultCredentials = true;
                  request.Proxy = new WebProxy(proxyUri, true);
                  request.Proxy.Credentials = System.Net.CredentialCache.DefaultCredentials;
               }
            }
         }

         return request;
      }

      void Refresh() {
         updateRequired_ = false;

         WebRequest request = CreateRequest("https://ultraschall.io/ultraschall_release.xml");
         if(request != null) {
            WebResponse response = request.GetResponse();
            XmlTextReader reader = new XmlTextReader(response.GetResponseStream());
            XmlDocument document = new XmlDocument();
            document.Load(reader);
            XmlElement root = document.DocumentElement;
            XmlNode enclosure = root.SelectSingleNode("//channel/item/enclosure");
            if(enclosure != null) {
               XmlAttributeCollection attributes = enclosure.Attributes;
               XmlAttribute attribute = attributes["sparkle:version"];
               if(attribute != null) {
                  Version remoteVersion = Version.ParseString(attribute.Value);
                  Version localVersion = Version.ParseString(QueryLocalVersion());
                  updateRequired_ = (localVersion < remoteVersion) == true;
               }
            }

            reader.Close();
         }
      }
   }
}
