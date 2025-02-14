public class ArrayOperations2D
{
   /**
      getTotal method.
      @param array A 2D array of integers.
      @return The total of the values stored in the
              argument array.
   */

   public static int getTotal(int[][] array)
   {
      int total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         for (int col = 0; col < array[row].length; col++)
            total += array[row][col];
      }
      
      return total;
   }

   /**
      getTotal method.
      @param array A 2D array of floats.
      @return The total of the values stored in the
              argument array.
   */
      
   public static float getTotal(float[][] array)
   {
      float total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         for (int col = 0; col < array[row].length; col++)
            total += array[row][col];
      }
      
      return total;
   }

   /**
      getTotal method.
      @param array A 2D array of doubles.
      @return The total of the values stored in the
              argument array.
   */
      
   public static double getTotal(double[][] array)
   {
      double total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         for (int col = 0; col < array[row].length; col++)
            total += array[row][col];
      }
      
      return total;
   }

   /**
      getTotal method.
      @param array A 2D array of longs.
      @return The total of the values stored in the
              argument array.
   */
      
   public static long getTotal(long[][] array)
   {
      long total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         for (int col = 0; col < array[row].length; col++)
            total += array[row][col];
      }
      
      return total;
   }

   /**
      getAverage method
      @param array A 2D array of integers.
      @return The average of the values stored in the
              argument array.
   */
      
   public static double getAverage(int[][] array)
   {
      // Cast the return value of getTotal so we don't
      // do integer division.
      return (double) getTotal(array) / getElementCount(array);
   }

   /**
      getAverage method
      @param array A 2D array of floats.
      @return The average of the values stored in the
              argument array.
   */
   
   public static double getAverage(float[][] array)
   {
      return getTotal(array) / getElementCount(array);
   }

   /**
      getAverage method
      @param array A 2D array of doubles.
      @return The average of the values stored in the
              argument array.
   */
   
   public static double getAverage(double[][] array)
   {
      return getTotal(array) / getElementCount(array);
   }

   /**
      getAverage method
      @param array A 2D array of longs.
      @return The average of the values stored in the
              argument array.
   */
   
   public static double getAverage(long[][] array)
   {
      return getTotal(array) / getElementCount(array);
   }


   /**
      getRowTotal method.
      @param array A 2D array of integers.
      @param row A specified row
      @return The total of the values stored in the
              specified row of the argument array.
   */

   public static int getRowTotal(int[][] array, int row)
   {
      int total = 0;
      
      for (int col = 0; col < array[row].length; col++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getRowTotal method.
      @param array A 2D array of floats.
      @param row A specified row
      @return The total of the values stored in the
              specified row of the argument array.
   */
   
   public static float getRowTotal(float[][] array, int row)
   {
      float total = 0;
      
      for (int col = 0; col < array[row].length; col++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getRowTotal method.
      @param array A 2D array of double.
      @param row A specified row
      @return The total of the values stored in the
              specified row of the argument array.
   */
   
   public static double getRowTotal(double[][] array, int row)
   {
      double total = 0;
      
      for (int col = 0; col < array[row].length; col++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getRowTotal method.
      @param array A 2D array of longs.
      @param row A specified row
      @return The total of the values stored in the
              specified row of the argument array.
   */
   
   public static long getRowTotal(long[][] array, int row)
   {
      long total = 0;
      
      for (int col = 0; col < array[row].length; col++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getColumnTotal method.
      @param array A 2D array of integers.
      @param col A specified col
      @return The total of the values stored in the
              specified column of the argument array.
   */
   
   public static int getColumnTotal(int[][] array, int col)
   {
      int total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getColumnTotal method.
      @param array A 2D array of floats.
      @param col A specified col
      @return The total of the values stored in the
              specified column of the argument array.
   */
   
   public static float getColumnTotal(float[][] array, int col)
   {
      float total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getColumnTotal method.
      @param array A 2D array of doubles.
      @param col A specified col
      @return The total of the values stored in the
              specified column of the argument array.
   */
   
   public static double getColumnTotal(double[][] array, int col)
   {
      double total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getColumnTotal method.
      @param array A 2D array of longs.
      @param col A specified col
      @return The total of the values stored in the
              specified column of the argument array.
   */
   
   public static long getColumnTotal(long[][] array, int col)
   {
      long total = 0;
      
      for (int row = 0; row < array.length; row++)
      {
         total += array[row][col];
      }
      
      return total;
   }

   /**
      getHighestInRow method.
      @param array A 2D array of integers.
      @param row A specified row.
      @return The highest value stored in the
              specified row of the argument array.
   */
   
   public static int getHighestInRow(int[][] array, int row)
   {
      int highest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] > highest)
            highest = array[row][col];
      }
      
      return highest;
   }

   /**
      getHighestInRow method.
      @param array A 2D array of floats.
      @param row A specified row.
      @return The highest value stored in the
              specified row of the argument array.
   */
   
   public static float getHighestInRow(float[][] array, int row)
   {
      float highest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] > highest)
            highest = array[row][col];
      }
      
      return highest;
   }

   /**
      getHighestInRow method.
      @param array A 2D array of doubles.
      @param row A specified row.
      @return The highest value stored in the
              specified row of the argument array.
   */
   
   public static double getHighestInRow(double[][] array, int row)
   {
      double highest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] > highest)
            highest = array[row][col];
      }
      
      return highest;
   }

   /**
      getHighestInRow method.
      @param array A 2D array of longs.
      @param row A specified row.
      @return The highest value stored in the
              specified row of the argument array.
   */
   
   public static long getHighestInRow(long[][] array, int row)
   {
      long highest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] > highest)
            highest = array[row][col];
      }
      
      return highest;
   }

   /**
      getLowestInRow method.
      @param array A 2D array of integers.
      @param row A specified row.
      @return The lowest value stored in the
              specified row of the argument array.
   */
   
   public static int getLowestInRow(int[][] array, int row)
   {
      int lowest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] < lowest)
            lowest = array[row][col];
      }
      
      return lowest;
   }

   /**
      getLowestInRow method.
      @param array A 2D array of floats.
      @param row A specified row.
      @return The lowest value stored in the
              specified row of the argument array.
   */
   
   public static float getLowestInRow(float[][] array, int row)
   {
      float lowest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] < lowest)
            lowest = array[row][col];
      }
      
      return lowest;
   }

   /**
      getLowestInRow method.
      @param array A 2D array of doubles.
      @param row A specified row.
      @return The lowest value stored in the
              specified row of the argument array.
   */
   
   public static double getLowestInRow(double[][] array, int row)
   {
      double lowest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] < lowest)
            lowest = array[row][col];
      }
      
      return lowest;
   }

   /**
      getLowestInRow method.
      @param array A 2D array of longs.
      @param row A specified row.
      @return The lowest value stored in the
              specified row of the argument array.
   */
   
   public static long getLowestInRow(long[][] array, int row)
   {
      long lowest = array[row][0];
      
      for (int col = 1; col < array[row].length; col++)
      {
         if (array[row][col] < lowest)
            lowest = array[row][col];
      }
      
      return lowest;
   }

   /**
      getElementCount method.
      @param array A 2D array of integers.
      @return The number of elements in the
              argument array.
   */
   
   public static int getElementCount(int[][] array)
   {
      int count = 0;

      for (int row = 0; row < array.length; row++)
         count += array[row].length;
      
      return count;
   }

   /**
      getElementCount method.
      @param array A 2D array of floats.
      @return The number of elements in the
              argument array.
   */
   
   public static int getElementCount(float[][] array)
   {
      int count = 0;

      for (int row = 0; row < array.length; row++)
         count += array[row].length;
      
      return count;
   }

   /**
      getElementCount method.
      @param array A 2D array of doubles.
      @return The number of elements in the
              argument array.
   */
   
   public static int getElementCount(double[][] array)
   {
      int count = 0;

      for (int row = 0; row < array.length; row++)
         count += array[row].length;
      
      return count;
   }

   /**
      getElementCount method.
      @param array A 2D array of longs.
      @return The number of elements in the
              argument array.
   */
   
   public static int getElementCount(long[][] array)
   {
      int count = 0;

      for (int row = 0; row < array.length; row++)
         count += array[row].length;
      
      return count;
   }
}
