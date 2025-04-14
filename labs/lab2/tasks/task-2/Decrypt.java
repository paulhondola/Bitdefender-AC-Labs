import java.io.ByteArrayOutputStream;
import java.util.Base64;

class Decrypt {

	public static String KEY = "npmanager";
	private static final String hexString = "0123456789ABCDEF";

	public static String d(byte[] bArr) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i = 0;
		while (true) {
			int i2 = i;
			if (i2 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i2)) << 4) | hexString.indexOf(str.charAt(i2 + 1))
			);
			i = i2 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i3 = 0; i3 < length; i3++) {
			byteArray[i3] = (byte) (byteArray[i3] ^ KEY.charAt(i3 % length2));
		}
		return new String(byteArray);
	}

	public static String d(byte[] bArr, boolean z) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i = 0;
		while (true) {
			int i2 = i;
			if (i2 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i2)) << 4) | hexString.indexOf(str.charAt(i2 + 1))
			);
			i = i2 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i3 = 0; i3 < length; i3++) {
			byteArray[i3] = (byte) (byteArray[i3] ^ KEY.charAt(i3 % length2));
		}
		return new String(byteArray);
	}

	public static String d(byte[] bArr, int i) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i2 = 0;
		while (true) {
			int i3 = i2;
			if (i3 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i3)) << 4) | hexString.indexOf(str.charAt(i3 + 1))
			);
			i2 = i3 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i4 = 0; i4 < length; i4++) {
			byteArray[i4] = (byte) (byteArray[i4] ^ KEY.charAt(i4 % length2));
		}
		return new String(byteArray);
	}

	public static String d(boolean z, byte[] bArr) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i = 0;
		while (true) {
			int i2 = i;
			if (i2 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i2)) << 4) | hexString.indexOf(str.charAt(i2 + 1))
			);
			i = i2 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i3 = 0; i3 < length; i3++) {
			byteArray[i3] = (byte) (byteArray[i3] ^ KEY.charAt(i3 % length2));
		}
		return new String(byteArray);
	}

	public static String d(int i, byte[] bArr) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i2 = 0;
		while (true) {
			int i3 = i2;
			if (i3 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i3)) << 4) | hexString.indexOf(str.charAt(i3 + 1))
			);
			i2 = i3 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i4 = 0; i4 < length; i4++) {
			byteArray[i4] = (byte) (byteArray[i4] ^ KEY.charAt(i4 % length2));
		}
		return new String(byteArray);
	}

	public static String d(boolean z, byte[] bArr, boolean z2) {
		String str = new String(Base64.getDecoder().decode(bArr));
		ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(str.length() / 2);
		int i = 0;
		while (true) {
			int i2 = i;
			if (i2 >= str.length()) {
				break;
			}
			byteArrayOutputStream.write(
				(hexString.indexOf(str.charAt(i2)) << 4) | hexString.indexOf(str.charAt(i2 + 1))
			);
			i = i2 + 2;
		}
		byte[] byteArray = byteArrayOutputStream.toByteArray();
		int length = byteArray.length;
		int length2 = KEY.length();
		for (int i3 = 0; i3 < length; i3++) {
			byteArray[i3] = (byte) (byteArray[i3] ^ KEY.charAt(i3 % length2));
		}
		return new String(byteArray);
	}

	public static String RlgCwZW() {
		return d(
			new byte[] {
				77,
				69,
				69,
				119,
				81,
				84,
				69,
				48,
				77,
				68,
				107,
				119,
				78,
				122,
				65,
				48,
				77,
				84,
				73,
				61,
			},
			true
		);
	}

	public static void main(String[] args) {
		System.out.println(RlgCwZW());
	}
}
