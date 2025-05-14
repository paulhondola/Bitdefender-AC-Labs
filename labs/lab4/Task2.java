import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;

public class Task2 {

	public static void main(String[] args) {
		try {
			// load png
			BufferedImage bitmap = ImageIO.read(new File("img/logo.png"));

			// convert bitmap to bytecode
			List<Byte> bytecode = new ArrayList<>();
			toRBitmap(bitmap, bytecode);

			byte[] bytes1 = fromBase63(bytecode);

			// write to dex file
			try (FileOutputStream stream = new FileOutputStream("malware_dex/task2.dex")) {
				stream.write(bytes1);
			}

			System.out.println("dex written successfully.");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static byte[] fromBase63(List<Byte> bytecode) {
		byte[] bytes = new byte[bytecode.size() / 2];
		for (int i = 0; i < bytecode.size(); i += 2) {
			byte highNibble = bytecode.get(i);
			byte lowNibble = bytecode.get(i + 1);
			bytes[i / 2] = (byte) ((highNibble << 4) | (lowNibble & 0x0F));
		}
		return bytes;
	}

	public static List<Byte> toRBitmap(BufferedImage img, List<Byte> out) {
		int width = img.getWidth();
		int height = img.getHeight();

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				int pixel = img.getRGB(x, y);
				int O = (pixel & 0x3) | ((pixel & 0x300) >>> 6) | ((pixel & 0x30000) >>> 12);

				if (O != 16) {
					out.add((byte) O);
				} else {
					return out;
				}
			}
		}

		return null;
	}
}
