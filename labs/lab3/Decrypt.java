import java.io.*;
import java.nio.charset.StandardCharsets;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

class Decrypt {

	public static void decrypt(File file, String str) {
		byte[] decryptedData = new byte[0];
		try {
			FileInputStream fileInputStream = new FileInputStream(file);
			try {
				byte[] encryptedBytes = new byte[(int) file.length()];
				fileInputStream.read(encryptedBytes);
				SecretKeySpec secretKeySpec = new SecretKeySpec(str.getBytes(), "AES");
				Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
				cipher.init(
					Cipher.DECRYPT_MODE,
					secretKeySpec,
					new IvParameterSpec("The BigIV's here".getBytes(StandardCharsets.UTF_8))
				);
				decryptedData = cipher.doFinal(encryptedBytes);
				fileInputStream.close();
			} finally {}
		} catch (Exception e3) {
			e3 = e3;
		}

		File decrypted = new File("decrypted.txt");
		try {
			FileOutputStream fileOutputStream = new FileOutputStream(decrypted);
			try {
				fileOutputStream.write(decryptedData);
				fileOutputStream.close();
			} finally {}
		} catch (Exception e4) {
			e4 = e4;
		}
	}

	public static void main(String[] args) {
		File file = new File("sdcard/Download/text.txt");

		File keyFile = new File("sdcard/SECRETS/nothingsecrethere");

		try {
			BufferedReader reader = new BufferedReader(new FileReader(keyFile));
			String line;
			while ((line = reader.readLine()) != null) {
				try {
					decrypt(file, line);
				} catch (Exception e) {
					e = e;
				}
			}
			reader.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
