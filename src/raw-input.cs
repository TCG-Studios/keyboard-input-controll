using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using System.Windows.Input;
//using HidLibrary;

namespace KIC {
    public class Input {
        public static void Main(){
            Console.WriteLine("test");
            IsInputFromKeyboardDevice();

            Console.WriteLine("test");
            getKeyboard();
        }
        
        private static void getKeyboard(){
            Console.WriteLine("test1");
            DateTime endTime = DateTime.Now.AddSeconds(60);
            while (DateTime.Now < endTime){
                Console.WriteLine(System.Windows.Input.ICommand.Equals());
            }
        }
        private bool IsInputFromKeyboardDevice(InputEventArgs e, string keyboardDeviceName)
        {
            Console.WriteLine(e);
            Console.WriteLine(keyboardDeviceName);
            if (e.Device is KeyboardDevice keyboardDevice)
            {
                return keyboardDevice.Name.Equals(keyboardDeviceName, StringComparison.OrdinalIgnoreCase);
            }

            return false;
        }
    }
}

