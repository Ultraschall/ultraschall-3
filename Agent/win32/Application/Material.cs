using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ultraschall {
   public class Material {
      public Material(String component, String version, String location) {
         this.component_ = component;
         this.version_ = version;
         this.location_ = location;
      }

      private String component_ = null;
      public String Component {
         get {
            return component_;
         }
      }

      private String version_ = null;

      public String Version {
         get {
            return this.version_;
         }
      }

      private String location_ = null;

      public String Location {
         get {
            return this.location_;
         }
      }
   }
}
