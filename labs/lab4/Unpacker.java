import java.io.*;
import java.util.*;

public class Unpacker {

	public static String readTextFile(String fileName) {
		String str;
		BufferedReader in;
		BufferedReader in2 = null;
		try {
			in = new BufferedReader(new InputStreamReader(new File(fileName)));
		} catch (IOException e) {} catch (Throwable th) {
			th = th;
		}
		try {
			StringBuilder buffer = new StringBuilder();
			while (true) {
				String line = in.readLine();
				if (line == null) {
					break;
				}
				buffer.append(line).append(System.getProperty("line.separator"));
			}
			str = buffer.toString();
			try {
				in.close();
			} catch (IOException e2) {
				e2.printStackTrace();
			}
		} catch (IOException e3) {
			in2 = in;
			str = "";
			try {
				in2.close();
			} catch (IOException e4) {
				e4.printStackTrace();
			}
			return str;
		} catch (Throwable th2) {
			th = th2;
			in2 = in;
			try {
				in2.close();
			} catch (IOException e5) {
				e5.printStackTrace();
			}
			throw th;
		}
		return str;
	}

	public static void main(String[] args) {
		String bin2hex = readTextFile("img/new.png");
		System.out.println(bin2hex);
	}
}
