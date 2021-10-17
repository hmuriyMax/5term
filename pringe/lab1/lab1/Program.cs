using System;

/*В каждом столбце двумерного массива A поставить на первое место
максимальный по модулю элемент столбца, определив после этого
среднее арифметическое элементов первой строки. Изменённый
двумерный массив должен содержать все элементы исходного.*/

namespace lab1
{
    class Program
    {
        static void PrntM(double[,] arr)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    Console.Write($"{arr[i, j]} \t");
                }
                Console.WriteLine();
            }
        }

        static void ScanM(ref double[,] arr)
        {
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    Console.Write($"[{i}, {j}]: ");
                    double tmp = Convert.ToDouble(Console.ReadLine());
                    arr[i, j] = tmp;
                }
            }
        }

        static double Lab1Swapper(ref double[,] arr)
        {
            double sum = 0;
            for (int j = 0; j < arr.GetLength(1); j++)
            {
                double maxClmn = arr[0, j];
                for (int i = 0; i < arr.GetLength(0); i++)
                {
                    if (Math.Abs(arr[i, j]) > Math.Abs(maxClmn))
                    {
                        maxClmn = arr[i, j];
                    }
                }
                arr[0, j] = maxClmn;
                sum += maxClmn;
            }
            return sum;
        }

        static void Main(string[] args)
        {
            int n = 0, m = 0;
            while (n < 1)
            {
                Console.Write("Size of matrix N: ");
                n = Convert.ToInt32(Console.ReadLine());
            }
            while (m < 1)
            {
                Console.Write("Size of matrix M: ");
                m = Convert.ToInt32(Console.ReadLine());
            }

            double[,] arr = new double[n, m];

            ScanM(ref arr);
            Console.WriteLine("Got matrix: ");
            PrntM(arr);
            double sum = Lab1Swapper(ref arr);
            Console.WriteLine("Result matrix: ");
            PrntM(arr);
            Console.WriteLine("Average of the first line is: {0:f2}", sum / m);
        }
    }
}
