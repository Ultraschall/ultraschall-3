using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using System.IO;
using System.Xml;
using System.Net;

namespace Ultraschall {
   public partial class MainWindow : Window {
      public MainWindow() {
         InitializeComponent();
      }

      private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e) {
         Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
         e.Handled = true;
      }

      private void Window_Loaded(object sender, RoutedEventArgs e) {
         UpdateStatus updateStatus = new UpdateStatus();
         if(updateStatus.UpdateRequired == true) {
            no_update_available.Visibility = Visibility.Hidden;
            update_available.Visibility = Visibility.Visible;
         }
         else {
            no_update_available.Visibility = Visibility.Visible;
            update_available.Visibility = Visibility.Hidden;
         }
      }

   }
}
