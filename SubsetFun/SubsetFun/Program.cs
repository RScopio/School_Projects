using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SubsetFun
{
    class Program
    {
        public static (List<int> subset, int sum) SubsetSum(int[] set)
        {
            //-3 2 6 4 -2 4 -3 -8 7 8

            //add to current set
            //create new subset if single value is larger than current set
            //keep track of largest set created thusfar

            int largestSum = set[0];
            int currentSum = set[0];
            List<int> subset = new List<int>() { set[0] };
            List<int> largestSubset = new List<int>() { set[0] };
            for (int i = 1; i < set.Length; i++)
            {
                int newSum = currentSum + set[i];
                if (set[i] > newSum)
                {
                    currentSum = set[i];
                    subset = new List<int>() { set[i] };
                }
                else
                {
                    currentSum = newSum;
                    subset.Add(set[i]);
                }

                if (currentSum > largestSum)
                {
                    largestSum = currentSum;
                    largestSubset = new List<int>(subset);
                }
            }

            return (largestSubset, largestSum);
        }



        static void Main(string[] args)
        {
            Random rand = new Random(Guid.NewGuid().GetHashCode());
            int size = 10;
            int[] set = new int[size];
            for (int i = 0; i < size; i++)
            {
                set[i] = rand.Next(-9, 10);
                Console.Write($"{set[i]} ");
            }
            Console.WriteLine("");

            (List<int> subset, int sum) subsetSum = SubsetSum(set);

            foreach (var item in subsetSum.subset)
            {
                Console.Write($"{item} ");
            }
            Console.WriteLine($"\n{subsetSum.sum}");
            Console.ReadKey();
        }
    }
}
