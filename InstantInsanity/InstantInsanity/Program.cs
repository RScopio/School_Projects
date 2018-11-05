using System;
using System.Collections.Generic;
namespace InstantInsanity
{
    public class Pair
    {
        public int[] colors = new int[2];
        public bool visited = false;
        public bool used = false;

        public Pair() { }

        public Pair(int colorA, int colorB)
        {
            colors[0] = colorA;
            colors[1] = colorB;
        }
    }

    public class Cube
    {
        public Pair[] opposites = new Pair[3];

        public Cube()
        {
            for (int i = 0; i < opposites.Length; i++)
            {
                opposites[i] = new Pair(0, 0);
            }
        }

        public Cube(Pair a, Pair b, Pair c)
        {
            opposites[0] = a;
            opposites[1] = b;
            opposites[2] = c;
        }

        public Cube(int colorRange, Random random)
        {
            for (int i = 0; i < opposites.Length; i++)
            {
                opposites[i] = new Pair(random.Next(1, colorRange + 1), random.Next(1, colorRange + 1));
            }
        }
    }

    class Program
    {
        static Random random = new Random();
        static bool Debug = false;

        //checks if able to add the pair to the bank 
        static bool CheckColors(List<Pair> bank, Pair pair, int colorRange)
        {
            if (bank.Count == 1)
            {
                return true;
            }

            Dictionary<int, int> usedColors = new Dictionary<int, int>();
            for (int i = 1; i <= colorRange; i++)
            {
                usedColors.Add(i, 0);
            }

            for (int i = 1; i < bank.Count; i++)
            {
                usedColors[bank[i].colors[0]]++;
                usedColors[bank[i].colors[1]]++;
            }

            usedColors[pair.colors[0]]++;
            usedColors[pair.colors[1]]++;

            if (usedColors[pair.colors[0]] <= 2 && usedColors[pair.colors[1]] <= 2)
            {
                return true;
            }
            return false;
        }
        static void FindThread(List<Pair> bank, Cube[] cubes, int n)
        {
            int longestSolution = 0;
            int level = 0;
            while (bank.Count != 0 && bank.Count != n + 1)
            {
                bank[level].visited = true;
                //left
                if (!cubes[level].opposites[0].visited && !cubes[level].opposites[0].used && CheckColors(bank, cubes[level].opposites[0], n))
                {
                    bank.Add(cubes[level].opposites[0]);
                    level++;
                    if (Debug) Console.WriteLine($"+({bank[level].colors[0]},{bank[level].colors[1]})");
                }
                //middle
                else if (!cubes[level].opposites[1].visited && !cubes[level].opposites[1].used && CheckColors(bank, cubes[level].opposites[1], n))
                {
                    bank.Add(cubes[level].opposites[1]);
                    level++;
                    if (Debug) Console.WriteLine($"+({bank[level].colors[0]},{bank[level].colors[1]})");
                }
                //right
                else if (!cubes[level].opposites[2].visited && !cubes[level].opposites[2].visited && CheckColors(bank, cubes[level].opposites[2], n))
                {
                    bank.Add(cubes[level].opposites[2]);
                    level++;
                    if (Debug) Console.WriteLine($"+({bank[level].colors[0]},{bank[level].colors[1]})");
                }
                else
                {
                    if (bank.Count > longestSolution)
                    {
                        longestSolution = bank.Count;
                    }
                    //clear visted from level and up
                    for (int i = level; i < cubes.Length; i++)
                    {
                        foreach (Pair p in cubes[i].opposites)
                        {
                            p.visited = false;
                        }
                    }
                    //pop
                    if (Debug) Console.WriteLine($"-({bank[level].colors[0]},{bank[level].colors[1]})");
                    bank.RemoveAt(bank.Count - 1);
                    level--;
                }
            }

            if (bank.Count == 0)
            {
                Console.WriteLine("No solution found!");
                Console.WriteLine($"Obstacle Size <= {longestSolution - 1}");
            }
            else
            {
                bank.RemoveAt(0);

                //mark used
                foreach (Pair p in bank)
                {
                    p.used = true;
                }

                //clear visited
                foreach (Cube c in cubes)
                {
                    foreach (Pair p in c.opposites)
                    {
                        p.visited = false;
                    }
                }
            }
        }
        static float ColorAverage(Cube c)
        {
            float total = 0;
            for (int i = 0; i < c.opposites.Length; i++)
            {
                total += c.opposites[i].colors[0];
                total += c.opposites[i].colors[1];
            }
            return total / 6;
        }
        static int FindMono(Cube[] c)
        {
            bool monoFound = false;
            int color = 0;
            for (int i = 0; i < c.Length; i++)
            {
                monoFound = true;
                color = c[i].opposites[0].colors[0];
                for (int j = 0; j < c[i].opposites.Length; j++)
                {
                    if (color != c[i].opposites[j].colors[0] ||
                       color != c[i].opposites[j].colors[0])
                    {
                        monoFound = false;
                        break;
                    }
                }

                if (monoFound) return i;
            }
            return -1;
        }
        static int FindAdj(Cube[] c, int color)
        {
            for (int i = 0; i < c.Length; i++)
            {
                int colorCount = 0;
                for (int j = 0; j < c[i].opposites.Length; j++)
                {
                    if (c[i].opposites[j].colors[0] == color)
                    {
                        colorCount++;
                        continue;
                    }
                    if (c[i].opposites[j].colors[1] == color)
                    {
                        colorCount++;
                        continue;
                    }
                }

                if (colorCount >= 2) return i;
            }

            return -1;
        }
        static void Puzzle(double equation)
        {
            int n = 32;
            Console.WriteLine($"#of cubes: {n}");

            Cube[] cubes = new Cube[n];
            for (int i = 0; i < cubes.Length; i++)
            {
                cubes[i] = new Cube();
            }

            //Setup Puzzle
            int a, b, c;
            a = b = c = 0;
            for (int i = 1; i <= 192; i++)
            {
                cubes[a].opposites[b].colors[c] = 1 + (int)(i * equation) % 32;
                c++;
                if (c > 1)
                {
                    c = 0;
                    b++;
                    if (b > 2)
                    {
                        b = 0;
                        a++;
                    }
                }
            }

            //print initial setup
            Console.WriteLine("#\tOpp1\tOpp2\tOpp3");
            for (int i = 0; i < cubes.Length; i++)
            {
                Console.Write($"{i + 1}");
                for (int j = 0; j < cubes[i].opposites.Length; j++)
                {
                    Console.Write($"\t({cubes[i].opposites[j].colors[0]},{cubes[i].opposites[j].colors[1]})");
                }
                Console.WriteLine("");
            }

            //Check for obstacles
            //Check for mono cube & cube with adj with same color
            int mono = FindMono(cubes);
            if (mono != -1)
            {
                Console.WriteLine("Mono cube found at");
                //Search for cube with an adjacent color
                int adj = FindAdj(cubes, cubes[mono].opposites[0].colors[0]);
                if (adj != -1)
                {
                    Console.WriteLine($"Obstacle Found: Mono cube at {mono} with similar adjs colors at cube {adj}");
                    return;
                }
            }
            else
            {
                Console.WriteLine("No mono cubes found");
            }

            //bubble sort by average color to increase search times
            Console.WriteLine("Sorting by average color...");
            bool sorting = true;
            while (sorting)
            {
                sorting = false;
                for (int i = 0; i < cubes.Length - 1; i++)
                {
                    if (ColorAverage(cubes[i]) > ColorAverage(cubes[i + 1]))
                    {
                        Cube temp = cubes[i + 1];
                        cubes[i + 1] = cubes[i];
                        cubes[i] = temp;
                        sorting = true;
                    }
                }
            }

            //Depth First Search for Solution
            Console.WriteLine("Searching for solution with compact Depth First Search...");
            List<Pair> bankA = new List<Pair>();
            bankA.Add(new Pair(0, 0));
            bankA.Add(cubes[0].opposites[1]);
            Console.Write("Thread A: ");
            FindThread(bankA, cubes, n);

            //Print Solution
            foreach (Pair p in bankA)
            {
                Console.Write($"({p.colors[0]},{p.colors[1]}) ");
            }
            if (bankA.Count != 0)
            {
                List<Pair> bankB = new List<Pair>();
                bankB.Add(new Pair(0, 0));
                Console.Write("\nThread B: ");
                FindThread(bankB, cubes, n);
                foreach (Pair p in bankB)
                {
                    Console.Write($"({p.colors[0]},{p.colors[1]}) ");
                }
            }

            Console.WriteLine("\n");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Puzzle One: ");
            Puzzle(Math.PI);
            Console.WriteLine("Puzzle Two: ");
            Puzzle(Math.E);
            Console.WriteLine("Done.");
            Console.ReadKey();
        }
    }
}
