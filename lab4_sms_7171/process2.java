import java.util.Scanner;
import java.io.*;
import java.lang.Runtime;
public class process2
{
        public static void main(String[] args)      throws InterruptedException,IOException {
                String comand = "Введите адрес: ";
                System.out.print(comand);
                Scanner in = new Scanner(System.in);
                String ip = in.nextLine();
                String com = "Введите начало диапазона: ";
		System.out.print(com);
                int first = in.nextInt();
		String com1 = "Введите конец диапазона: ";
                System.out.print(com1);
                int second = in.nextInt();
		in.close();
		ip = ip+".";
		for (int i = first; i<second; i++)
		{
			String temp_ = ip; 	// Заносим диапазон адресов в строку
			String temp = Integer.toString(i);
			temp_ +=temp; // Адрес для опроса
		//	Process pr = Runtime.getRuntime().exec("./proc1.jar");
			Process pr = Runtime.getRuntime().exec("ping -c 1 "+temp_); //Запуск процесса
	 		String line=null;
           		BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
             		while((line=input.readLine()) != null) System.out.println(line);
		}
        }
}
