using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ultraschall {
   public class Version {
      private const int MAX_TOKEN_COUNT = 4;

      private int[] numbers_ = new int[MAX_TOKEN_COUNT] { 0, 0, 0, 0 };

      public static Version ParseString(String str) {
         Version version = null;
         if(String.IsNullOrEmpty(str) == false) {
            String[] tokens = str.Split(("., ").ToCharArray());
            if(tokens.Length > 0) {
               version = new Version();
               int validTokenCount = 0;
               int readTokenCount = 0;
               while((readTokenCount < MAX_TOKEN_COUNT) && (readTokenCount < tokens.Length)) {
                  String token = tokens[readTokenCount].Trim();
                  int number = -1;
                  if(int.TryParse(token, out number) == true) {
                     version.numbers_[validTokenCount] = number;
                     validTokenCount++;
                  }

                  readTokenCount++;
               }
            }
         }

         return version;
      }

      public static bool IsNullOrEmpty(Version version) {
         return (version == null) || (version.numbers_ == new int[MAX_TOKEN_COUNT] { 0, 0, 0, 0 });
      }

      private int? NumberAtIndex(int index) {
         int? number = null;
         if((index >= 0) && (index < MAX_TOKEN_COUNT)) {
            number = numbers_[index];
         }

         return number;
      }
      public int? this[int index] {
         get {
            return NumberAtIndex(index);
         }
      }

      private static bool Equal(Version lhs, Version rhs) {
         bool equal = false;
         if((Version.IsNullOrEmpty(lhs) == false) && (Version.IsNullOrEmpty(rhs) == false)) {
            bool[] flags = new bool[MAX_TOKEN_COUNT] { false, false, false, false };
            for(int i = 0; (i < MAX_TOKEN_COUNT) && (equal == false); i++) {
               if(lhs.numbers_[i] == rhs.numbers_[i]) {
                  flags[i] = true;
               }
            }

            equal = flags.Count(flag => (flag == false)) == 0;
         }
         else {
            equal = false;
         }

         return equal;
      }

      //public static bool operator==(Version lhs, Version rhs) {
      //   return Version.Equal(lhs, rhs) == true;
      //}

      //public static bool operator !=(Version lhs, Version rhs) {
      //   return (lhs == rhs) == false;
      //}

      private static bool LessThan(Version lhs, Version rhs) {
         bool less = false;

         if((Version.IsNullOrEmpty(lhs) == false) && (Version.IsNullOrEmpty(rhs) == false)) {
            for(int i = 0; (i < MAX_TOKEN_COUNT) && (less == false); i++) {
               if(lhs.numbers_[i] < rhs.numbers_[i]) {
                  less = true;
               }
            }
         }

         return less;
      }

      public static bool operator<(Version lhs, Version rhs) {
         return LessThan(lhs, rhs) == true;
      }

      public static bool operator>(Version lhs, Version rhs) {
         return (lhs != rhs) && ((lhs < rhs) == false);
      }
   }
}
