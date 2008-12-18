using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace APD
{
    class AltUSB
    {

        private static IntPtr usbReadHandle = IntPtr.Zero;
        private static IntPtr usbWriteHandle = IntPtr.Zero;
        public static byte[] Usb_write_array = new byte[Constants.PACKET_SIZE];
        public static byte[] Usb_read_array = new byte[Constants.PACKET_SIZE];
        public static String FirmwareVersion = "NA";

        public static Constants.AltBoardUSB DetectPICkit2Device(ushort pk2ID)
        {
            IntPtr usbRdTemp = IntPtr.Zero;
            IntPtr usbWrTemp = IntPtr.Zero;

            bool result = USB.Find_This_Device(Constants.MChipVendorID, Constants.Pk2DeviceID,
                                 pk2ID, ref usbRdTemp, ref usbWrTemp);

            usbReadHandle = usbRdTemp;
            usbWriteHandle = usbWrTemp;

            if (result)
            {
                byte[] commandArray = new byte[1];
                commandArray[0] = Constants.GET_FIRMWARE_VERSION;
                result = writeUSB(commandArray);
                if (result)
                {
                    // read response
                    if (readUSB())
                    {
                        FirmwareVersion = string.Format("{0:D1}.{1:D2}.{2:D2}", Usb_read_array[1],
                                    Usb_read_array[2], Usb_read_array[3]);
                        return Constants.AltBoardUSB.found;
                    }
                    return Constants.AltBoardUSB.readError;
                }
                return Constants.AltBoardUSB.writeError;
            }
            return Constants.AltBoardUSB.notFound;

        }

        public static bool writeUSB(byte[] commandList)
        {
            int bytesWritten = 0;

            //USB_BYTE_COUNT += commandList.Length;
            //USB_BYTE_COUNT++;

            Usb_write_array[0] = 0;                         // first byte must always be zero.        
            for (int index = 1; index < Usb_write_array.Length; index++)
            {
                Usb_write_array[index] = Constants.END_OF_BUFFER;              // init array to all END_OF_BUFFER cmds.
            }
            Array.Copy(commandList, 0, Usb_write_array, 1, commandList.Length);
            bool writeResult = USB.WriteFile(usbWriteHandle, Usb_write_array, Usb_write_array.Length, ref bytesWritten, 0);
            if (bytesWritten != Usb_write_array.Length)
            {
                return false;
            }
            return writeResult;

        }

        public static bool readUSB()
        {
            int bytesRead = 0;

            bool readResult = USB.ReadFile(usbReadHandle, Usb_read_array, Usb_read_array.Length, ref bytesRead, 0);
            if (bytesRead != Usb_read_array.Length)
            {
                return false;
            }
            return readResult;
        }

        public static void DisconnectPICkit2Unit()
        {
            usbReadHandle = IntPtr.Zero;
            usbWriteHandle = IntPtr.Zero;
        }
        public static byte ReadEEByte(ushort address, byte block)
        {
            byte[] commandArray = new byte[4];
            //commandArray[0] = Constants.READ_EEPROM_BYTE;
            commandArray[1] = (byte)(address >> 8);
            commandArray[2] = (byte)(address & 0xFF);
            commandArray[3] = block;
            if (writeUSB(commandArray))
            {
                if (readUSB())
                {
                    return Usb_read_array[1];
                }
                return 0xFF;
            }

            return 0xFF;
        }

        public static byte[] ReadEE(ushort address, byte block, byte length)
        {
            byte[] result = new byte[length];
            byte[] commandArray = new byte[4];
            commandArray[0] = Constants.READ_EEPROM;
            commandArray[1] = (byte)(address >> 8);
            commandArray[2] = (byte)(address & 0xFF);
            commandArray[3] = block;
            if (writeUSB(commandArray))
            {
                if (readUSB())
                {
                    Array.Copy(Usb_read_array, 1, result, 0, length);
                    return result;
                }
                return null;
            }

            return null;
        }
        public static void ControlBuzzer(bool on)
        {
            byte[] commandArray = new byte[1];
            if(on)
                commandArray[0] = Constants.ENABLE_BUZZER;
            else
                commandArray[0] = Constants.DISABLE_BUZZER;

            writeUSB(commandArray);
        }
    }
}
