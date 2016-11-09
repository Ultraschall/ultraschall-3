using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;
using System.Collections.ObjectModel;

namespace Ultraschall {
   public class BillOfMaterials : ObservableCollection<Material> {
      public BillOfMaterials() : base() {
         foreach(KeyValuePair<MaterialId, String> path in Paths) {
            if(path.Key != MaterialId.ULTRASCHALL_THEME) {
               Tuple<String, String> material = QueryFileVersionAndName(path.Value);
               Add(new Material(Names[path.Key], material.Item1, material.Item2));
            }
            else {
               String version = ThemeResolver.ResolveVersion(path.Value);
               Add(new Material(Names[path.Key], version, Paths[path.Key]));
            }
         }
      }

      public enum MaterialId {
         ULTRASCHALL_THEME,
         ULTRASCHALL_EXTENSION,
         ULTRASCHALL_SOUNDBOARD,
         STUDIO_LINK,
         LAME_ENCODER,
         SWS_EXTENSION,
         REAPER
      };

      private String applicationDataPath_ = null;
      private String ApplicationDataPath {
         get {
            if(applicationDataPath_ == null) {
               applicationDataPath_ = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);

            }

            return applicationDataPath_;
         }
      }

      private String programFilesPath_ = null;
      private String ProgramFilesPath {
         get {
            if(programFilesPath_ == null) {
               programFilesPath_ = Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles);

            }

            return programFilesPath_;
         }
      }

      private static Dictionary<MaterialId, String> paths_ = null;

      public Dictionary<MaterialId, String> Paths {
         get {
            if(paths_ == null) {
               paths_ = new Dictionary<MaterialId, String>();
               paths_.Add(MaterialId.ULTRASCHALL_THEME, ApplicationDataPath + @"\REAPER\ColorThemes\Ultraschall_2.2.ReaperThemeZip");
               paths_.Add(MaterialId.ULTRASCHALL_EXTENSION, ProgramFilesPath + @"\REAPER (x64)\Plugins\reaper_ultraschall.dll");
               paths_.Add(MaterialId.ULTRASCHALL_SOUNDBOARD, ProgramFilesPath + @"\Steinberg\VstPlugins\soundboard64.dll");
               paths_.Add(MaterialId.STUDIO_LINK, ProgramFilesPath + @"\Steinberg\VstPlugins\studio-link.dll");
               paths_.Add(MaterialId.LAME_ENCODER, ApplicationDataPath + @"\REAPER\UserPlugins\libmp3lame.dll");
               paths_.Add(MaterialId.SWS_EXTENSION, ProgramFilesPath + @"\REAPER (x64)\Plugins\reaper_sws64.dll");
               paths_.Add(MaterialId.REAPER, ProgramFilesPath + @"\REAPER (x64)\reaper.exe");
            }

            return paths_;
         }
      }

      private static Dictionary<MaterialId, String> names_ = null;

      public Dictionary<MaterialId, String> Names {
         get {
            if(names_ == null) {
               names_ = new Dictionary<MaterialId, String>();

               names_.Add(MaterialId.ULTRASCHALL_THEME, @"ULTRASCHALL REAPER Theme");
               names_.Add(MaterialId.ULTRASCHALL_EXTENSION, @"ULTRASCHALL REAPER Extension");
               names_.Add(MaterialId.ULTRASCHALL_SOUNDBOARD, @"ULTRASCHALL Soundboard");
               names_.Add(MaterialId.STUDIO_LINK, @"ITSR StudioLink Plug-in");
               names_.Add(MaterialId.SWS_EXTENSION, @"SWS REAPER Extension");
               names_.Add(MaterialId.LAME_ENCODER, @"LAME MP3 Encoder");
               names_.Add(MaterialId.REAPER, "Cockos REAPER");
            }

            return names_;
         }
      }

      private Tuple<String, String> QueryFileVersionAndName(String path) {
         String version = @"not installed";
         String name = @"unknown";

         if(File.Exists(path) == true) {
            FileVersionInfo versionInfo = FileVersionInfo.GetVersionInfo(path);
            version = versionInfo.ProductVersion;
            name = versionInfo.FileName;
         }

         return new Tuple<String, String>(version, name);
      }
   }
}
