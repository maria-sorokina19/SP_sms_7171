import java.util.Scanner;
import java.io.*;

public class Main
{
	public static void main(String[] args)      throws InterruptedException,IOException {
		Object[] arrayOfObjects;
		String str ="ping -c 1 ";
		String comand = "Введите адрес: ";
		System.out.print(comand);
		Scanner in = new Scanner(System.in); //Ввод адреса с клавиатуры
		String ip = in.nextLine();
        	in.close();
		str += ip;
		Process pr = Runtime.getRuntime().exec(str); //Запуск процесса
		String line=null;
           	BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
            	while((line=input.readLine()) != null) System.out.println(line);
	}
}
