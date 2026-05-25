using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

namespace ConsoleApp1
{
    internal class Program
    {
        static int Count = 0;
        const byte XON = 17;
        const byte XOFF = 19;

        static void Main(string[] args)
        {
            SerialPort port = new SerialPort("COM6", 9600, Parity.None, 8, StopBits.One);
            port.Handshake = Handshake.XOnXOff;
            port.Open();
            port.DataReceived += Port_DataReceived;


            List<byte> data = new List<byte>();
            for (char i= 'a';i<='z';i++) data.Add((byte)i);
            
            port.Write(data.ToArray(), 0, data.Count);

            while (port.BytesToRead>0) 
            { 
                Thread.Sleep(1000);
            };
            Console.WriteLine(Count);
        }

        private static void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            var port  = (SerialPort)sender;
            int count = port.BytesToRead;

            Count += count;
            byte[] ByteArray = new byte[count];
            port.Read(ByteArray, 0, count);

            foreach (byte b in ByteArray) Console.Write($"{(char)b} ");
        }
    }
}
