#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

void RSA_decryption(mpz_t plaintext, mpz_t ciphertext, mpz_t d, mpz_t n)
{
    mpz_powm(plaintext, ciphertext, d, n);
}

int main()
{
    FILE* fptr;
    FILE* private_key;
    FILE* public_key;
    FILE* key_data;
    private_key = fopen("private_key.txt", "r");
    public_key = fopen("public_key.txt", "r");
    key_data = fopen("RSA_key_data", "r");
    fptr = fopen("ciphertext.txt", "r");
    mpz_t d;
    gmp_fscanf(private_key, "%Zd", d);
    gmp_printf("d = %Zd\n", d);
    fclose(private_key);
    mpz_t p, q;
    char buffer1[310], buffer2[310];
    gmp_fscanf(key_data, "%[^\n] %[^\n]", buffer1, buffer2);
    mpz_init_set_str(p, buffer1, 10);
    mpz_init_set_str(q, buffer2, 10);
    fclose(key_data);
    gmp_printf("p = %Zd\nq= %Zd\n", p, q);
    mpz_t n, Phi_n;
    mpz_inits(n, Phi_n, NULL);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(Phi_n, p, q);
    gmp_printf("n = %Zd\nPhi(n) = %Zd\n$$$$\n", n, Phi_n);
    
    char c;
    mpz_t pt, ct;
    mpz_inits(pt, ct, NULL);
    char* buffer;
    buffer = (char*) malloc(620);
    int i = 0;
    FILE* wptr;
    wptr = fopen("decryptedtext.txt", "w");
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
            gmp_fprintf(wptr, "%Zd\n", pt);
            free(buffer);
            buffer = (char*) malloc(620);
            i = 0;
        }
    }
    gmp_printf("\n");
    fclose(fptr);
    fclose(wptr);
    return 0;
}

/*
5003228161865411606549847125302307810287785995690400374275594815868567932223078479136863441216250498175264467335294731956147067337005686636695256069012344143693713231522495887186045746975265348916822740954376066231783092730882070837388617783452765085559690815369445711183074103044639532361550311980495463878912190204913434586227913884918535092353997811022710459607481733997869547745914741606726976684050540746051084696066247977142646725373560807802130417187220828586630451218724206713500257083453843657612165071930605843195276208195715633111455209494355494652553212610314833132557559291474942309452903356651129954036139223930027814785401542990631974750276355287465733214515273686127989005798281814098383925545181913618683643757027415980553856985082103348890106812621947332262475631541790410072551586360441145472179607804976902014404693162795302688712597045167521901260757932677478967991072518732091320645294950419715846271802100910421320201094298653356646858355074485294355973852752611627122739273880998273938670089623641227463206183394651382273400725499873772992644963360398212724706267866560302660468467415258803195127802254688434242533548708715896884291573413335870088287413736422789109528609652151915552497743361583410938908881
*/