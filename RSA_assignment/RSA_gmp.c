#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void RSA_encryption(mpz_t plaintext, mpz_t e, mpz_t n, mpz_t ciphertext)
{
    mpz_powm(ciphertext, plaintext, e, n);
}

void RSA_decryption(mpz_t plaintext, mpz_t ciphertext, mpz_t d, mpz_t n)
{
    mpz_powm(plaintext, ciphertext, d, n);
}

void RSA_key_generation(mpz_t e, mpz_t d, mpz_t p, mpz_t q, FILE* private_file, FILE* public_file)
{
    mpz_t n, Phi_n, p_1, q_1;
    mpz_init(n);
        mpz_mul(n, p, q);
    mpz_init(Phi_n);
    mpz_inits(p_1, q_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
        mpz_mul(Phi_n, p_1, q_1);
    gmp_printf("n = %Zd\nPhi(n) = %Zd\n", n, Phi_n);
    int found = 0;
    // Create a Random GMP state
    gmp_randstate_t state;
    //gmp_randseed_ui(state, time(0));
    gmp_randinit_default(state); // Initialize it
    mpz_t gcd;
    mpz_init(gcd);
    while(!found)
    {
        
        mpz_urandomm(e, state, Phi_n);
        mpz_gcd(gcd, e, Phi_n);
        // Check if the GCD is 1,
        // if it is we have found a number which is coprime to Phi(n) 
        if(mpz_cmp_ui(gcd, 1) == 0){
            found = 1; 
        }
    }
    gmp_printf("E = %Zd\n", e);
    // 'd' can be found by taking MI of 'e' w.r.t Phi(n)
    mpz_invert(d, e, Phi_n);
    gmp_printf("D = %Zd\n", d);
    // Now save 'e' and 'd' in separate files. 
    // One will be private and kept secret.
    // Other will be shared with people. i.e. Public 
    mpz_out_str(private_file, 10, d);
    mpz_out_str(public_file, 10, e);
    // Clear the memory
    mpz_clears(p_1, q_1, gcd, Phi_n, n);
}

int main(int argc, char* argv[])
{
    //gmp_randseed_ui (gmp_randstate_t state, unsigned long int seed)
    printf("RSA using GMP:\n");
    int opt;
    int finish = 0;
    FILE *fptr;
    fptr = fopen("RSA_key_data", "r");
    if(fptr == NULL)
    {
        printf("File does not exist!\n");
        exit(1);
    }
    mpz_t p, q;

    char buffer1[310], buffer2[310];// buffer3[309], buffer4[309];
    gmp_fscanf(fptr, "%[^\n] %[^\n]", buffer1, buffer2);
    mpz_init_set_str(p, buffer1, 10);
    mpz_init_set_str(q, buffer2, 10);
    if(mpz_probab_prime_p(p, 15) == 0 || mpz_probab_prime_p(q, 15) == 0)
    {
        printf("Onr of p or q is probably NOT a prime number, select another numbers in the RSA_key_data file\n");
        mpz_clears(p, q);
    }
    fclose(fptr);
    mpz_t e, d; 
    mpz_inits(e, d, NULL);

    FILE* private_file;
    FILE* public_file;
    char* file_path;
    while(!finish)
    {
        printf("1) Generate new keys\n");
        printf("2) Encrypt a message\n");
        printf("3) Decrypt a message\n");
        printf("0) Exit\n");
        printf("\nEnter appropriate option: ");
        scanf("%d", &opt);
        switch(opt)
        {
            case 0:
                finish = 1;
                printf("Thank you!\n");
                // Clear all the variables
                mpz_clear(p);mpz_clear(q);mpz_clear(e); mpz_clear(d);
                break;
            case 1:
                private_file = fopen("private_key.txt", "w");
                public_file = fopen("public_key.txt", "w");
                RSA_key_generation(e,d,p,q,private_file,public_file);
                fclose(public_file);
                fclose(private_file);
                break;
            case 2:
            {
                fptr = fopen("plaintext.txt", "r");
                FILE* wptr = fopen("ciphertext.txt", "w");
                mpz_t pt, ct;
                mpz_inits(pt, ct, NULL);
                int c;
                gmp_printf("e = %Zd\n", e);
                if(mpz_cmp_ui(e, 0) != 0)
                {
                    mpz_t n;
                    mpz_init(n);
                    mpz_mul(n, p, q);
                    while((c = fgetc(fptr)) != EOF)
                    {
                        //printf("%ld\n", (unsigned long int) c);
                        mpz_set_ui(pt, (unsigned long int) c);
                        gmp_printf("pt = %Zd ", pt);
                        RSA_encryption(pt, e, n, ct);
                        gmp_fprintf(wptr, "%Zd\n", ct);
                    }
                    gmp_printf("Encryption completed! Check ciphertext.txt file\n");
                    fclose(fptr);
                    fclose(wptr);
                    mpz_clear(n);
                }
                else if(mpz_cmp_ui(e, 0) == 0)
                {
                    // Read from file
                    printf("Reading from file!\n");
                    public_file = fopen("public_key.txt", "r");
                    if(public_file == NULL){
                        printf("File doesn't exist\n");
                    }else{
                        
                        gmp_fscanf(public_file, "%Zd", e);
                        gmp_printf("ESTR = %Zd\n",e);
                        mpz_t n;
                        mpz_init(n);
                        mpz_mul(n, p, q);
                        while((c = fgetc(fptr)) != EOF)
                        {
                            mpz_set_ui(pt, (long) c);
                            RSA_encryption(pt, e, n, ct);
                            gmp_fprintf(wptr, "%Zd\n", ct);
                        }
                        gmp_printf("\nEncryption completed! Check ciphertext.txt file\n");
                        fclose(fptr);
                        fclose(wptr);
                        mpz_clear(n);
                    }
                }
                //mpz_clears(pt, ct);
                break;
            }    
            case 3:
            {
                fptr = fopen("ciphertext.txt", "r");
                FILE* wptr = fopen("decryptedtext.txt", "w");
                mpz_t pt, ct;
                mpz_inits(pt, ct, NULL);
                int plain_text_int = 0;
                if(mpz_cmp_ui(d, 0) != 0)
                {
                    mpz_t n;
                    mpz_init(n);
                    mpz_mul(n, p, q);
                    char* buffer;
                    buffer = (char*) malloc(620);
                    int i = 0;
                    char c;
                    
                    while((c = fgetc(fptr)) != EOF)
                    {
                        //
                        if(c != '\n')
                        {
                            buffer[i] = c;
                            i += 1;
                        }
                        else
                        {
                            //printf("One big number read! i = %d\n", i);
                            buffer[i] = '\0';
                            mpz_set_str(ct, buffer, 10);
                            //gmp_printf("$$$$$\n%Zd\n", ct);
                            RSA_decryption(pt, ct, d, n);
                            plain_text_int = (int) mpz_get_ui(pt);
                            gmp_fprintf(wptr, "%c", (char) plain_text_int);
                            free(buffer);
                            buffer = (char*) malloc(620);
                            i = 0;
                        }
                    }
                    gmp_printf("Decryption completed! Check decryptedtext.txt file\n");
                    
                    fclose(fptr);
                    fclose(wptr);
                }
                else if(mpz_cmp_ui(d, 0) == 0)
                {
                    // Read from file
                    printf("Reading from file!\n");
                    private_file = fopen("private_key.txt", "r");
                    if(private_file == NULL){
                        printf("File doesn't exist\n");
                    }else{
                        
                        gmp_fscanf(private_file, "%Zd", d);
                        gmp_printf("DSTR = %Zd\n",e);
                        mpz_t n;
                        mpz_init(n);
                        mpz_mul(n, p, q);
                        char* buffer;
                        buffer = (char*) malloc(620);
                        int i = 0;
                        char c;
                        while((c = fgetc(fptr)) != EOF) // Bugs here!
                        {
                            //
                            if(c != '\n')
                            {
                                buffer[i] = c;
                                i += 1;
                            }
                            else
                            {
                                printf("One big number read! i = %d\n", i);
                                buffer[i] = '\0';
                                mpz_set_str(ct, buffer, 10);
                                //gmp_printf("$$$$$\n%Zd\n", ct);
                                RSA_decryption(pt, ct, d, n);
                                plain_text_int = (int) mpz_get_ui(pt);
                                gmp_fprintf(wptr, "%c", (char) plain_text_int);
                                free(buffer);
                                buffer = (char*) malloc(620);
                                i = 0;
                            }
                        }
                        gmp_printf("Decryption completed! Check decryptedtext.txt file\n");
                        fclose(fptr);
                        fclose(wptr);
                    }
                }
                
                break;
            }
            default:

                printf("Enter correct option\n");
                break;  
        }
    }

    return 0;
}
// gcc RSA_gmp.c -lgmp -fno-stack-protector -o RSA
// ./RSA