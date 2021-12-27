using System;
using System.IO;
using System.Linq;
using System.Text;

namespace lab7
{
    class Program
    {
        internal static void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            Encoding iso = Encoding.GetEncoding("ISO-8859-1");
            Encoding utf16LE = Encoding.Unicode;

            var sr = new StreamReader("input.txt");

            var text = sr.ReadToEnd();

            if (text != "")
            {

                var c = Encoding.Default.GetChars(Encoding.Default.GetBytes(text)); //получаю массив char[]

                byte[] utf16Bytes = utf16LE.GetBytes(c);
                byte[] isoBytes = Encoding.Convert(utf16LE, iso, utf16Bytes);
                string outstr = iso.GetString(isoBytes);
                using (StreamWriter sw = new StreamWriter("output.txt", false, Encoding.GetEncoding("ISO-8859-1")))
                {
                    sw.WriteLine(outstr);
                }

            }
        }
    }
}
