using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MorseCount
{
    class Program
    {
        static Dictionary<string, string> MorseConvert = new Dictionary<string, string>(72)
        {
            [".-"] = "A",
            ["-..."] = "B",
            ["-.-."] = "C",
            ["-.."] = "D",
            ["."] = "E",
            ["..-."] = "F",
            ["--."] = "G",
            ["...."] = "H",
            [".."] = "I",
            [".---"] = "J",
            ["-.-"] = "K",
            [".-.."] = "L",
            ["--"] = "M",
            ["-."] = "N",
            ["---"] = "O",
            [".--."] = "P",
            ["--.-"] = "Q",
            [".-."] = "R",
            ["..."] = "S",
            ["-"] = "T",
            ["..-"] = "U",
            ["...-"] = "V",
            [".--"] = "W",
            ["-..-"] = "X",
            ["-.--"] = "Y",
            ["--.."] = "Z",
            [".----"] = "1",
            ["..---"] = "2",
            ["...--"] = "3",
            ["....-"] = "4",
            ["....."] = "5",
            ["-...."] = "6",
            ["--..."] = "7",
            ["---.."] = "8",
            ["----."] = "9",
            ["-----"] = "0",

            ["A"] = ".-",
            ["B"] = "-...",
            ["C"] = "-.-.",
            ["D"] = "-..",
            ["E"] = ".",
            ["F"] = "..-.",
            ["G"] = "--.",
            ["H"] = "....",
            ["I"] = "..",
            ["J"] = ".---",
            ["K"] = "-.-",
            ["L"] = ".-..",
            ["M"] = "--",
            ["N"] = "-.",
            ["O"] = "---",
            ["P"] = ".--.",
            ["Q"] = "--.-",
            ["R"] = ".-.",
            ["S"] = "...",
            ["T"] = "-",
            ["U"] = "..-",
            ["V"] = "...-",
            ["W"] = ".--",
            ["X"] = "-..-",
            ["Y"] = "-.--",
            ["Z"] = "--..",
            ["1"] = ".----",
            ["2"] = "..---",
            ["3"] = "...--",
            ["4"] = "....-",
            ["5"] = ".....",
            ["6"] = "-....",
            ["7"] = "--...",
            ["8"] = "---..",
            ["9"] = "----.",
            ["0"] = "-----"
        };


        static HashSet<string> GetMorseVariations(string morseCode)
        {
            HashSet<string> set = new HashSet<string>();
            throw new NotImplementedException();
            return set;
        }

        static string TryGetMorse(string morse)
        {
            try
            {
                return MorseConvert[morse];
            }
            catch (KeyNotFoundException)
            {
                return null;
            }
        }

        static string RandomMorseCode(int length)
        {
            Random gen = new Random(Guid.NewGuid().GetHashCode());
            string output = "";
            for (int i = 0; i < length; i++)
            {
                output += gen.NextDouble() < 0.5f ? "." : "-";
            }
            return output;
        }

        static void Main(string[] args)
        {
            string test = RandomMorseCode(10);
            Console.WriteLine(test);
            var set = GetMorseVariations(test);
            foreach(var word in set)
            {
                Console.WriteLine(word);
            }
            Console.ReadKey();
        }
    }
}
