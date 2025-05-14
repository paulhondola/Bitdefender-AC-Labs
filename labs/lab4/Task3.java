import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.Base64;

public class Task3 {

	// paths for input / output
	private static final Path INPUT = Paths.get("img", "new.png");
	private static final Path OUTPUT = Paths.get("malware_dex", "task3.dex");

	public static void main(String[] args) {
		try {
			// read the entire file as UTF-8 text
			byte[] allBytes = Files.readAllBytes(INPUT);

			// find the last '#' byte
			int lastHash = -1;
			for (int i = allBytes.length - 1; i >= 0; i--) {
				if (allBytes[i] == (byte) '#') {
					lastHash = i;
					break;
				}
			}

			// no marker found
			if (lastHash < 0 || lastHash == allBytes.length - 1) {
				System.err.println("No '#' marker found or nothing after it.");
				return;
			}

			// extract everything after '#' as ASCII/Base64
			String b64 = new String(
				allBytes,
				lastHash + 1,
				allBytes.length - lastHash - 1,
				StandardCharsets.US_ASCII
			);

			// 4) Decode and write dex
			byte[] dex = Base64.getDecoder().decode(b64);
			Files.write(
				OUTPUT,
				dex,
				StandardOpenOption.CREATE,
				StandardOpenOption.TRUNCATE_EXISTING
			);

			System.out.println("Wrote DEX to " + OUTPUT.toAbsolutePath());
		} catch (IOException e) {
			System.err.println("I/O error: " + e.getMessage());
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			System.err.println("Base64 decoding failed: " + e.getMessage());
			e.printStackTrace();
		}
	}
}
