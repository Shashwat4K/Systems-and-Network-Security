import java.util.Scanner;

class AutokeyCipher
{
    public String autokeyEncryption(String plaintext, char k1)
    {
        char[] chararray = plaintext.toCharArray();
        char prev, prev2;
        prev = chararray[0]; 
        chararray[0] = (char) ((((int)(chararray[0] - 'a') + (int)(k1 - 'a')) % 26) + 'a');
        for(int i = 1; i < chararray.length; i++){
            prev2 = chararray[i];
            chararray[i] = (char) ((((int)(chararray[i] - 'a') + (int)(prev - 'a')) % 26) + 'a');
            prev = prev2;
        }
        return String.valueOf(chararray);
    }

    public static void main(String args[])
    {
        String plaintext;
        String key;
        String cipher;
        Scanner sc = new Scanner(System.in);
        AutokeyCipher obj = new AutokeyCipher();
        try {
            System.out.println("Enter Plaintext: ");
            plaintext = sc.next();
            System.out.println("Enter key: (single character)");
            key = sc.next();

            cipher = obj.autokeyEncryption(plaintext, key.charAt(0));
            System.out.println("Encrypted Cipher is: " + cipher);

        } catch (Exception e) {
            
            System.err.println("Error! check your code");
        } finally{
            if(sc != null){
                sc.close();
            }
        }
    }
}
