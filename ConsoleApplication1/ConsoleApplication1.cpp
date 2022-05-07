// ConsoleApplication1.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <Windows.h>
#include <fstream>

int tot_count = 0;

void* rdfile(int* porsize, const char* filename)
{
    FILE* f = fopen(filename, "rb");
    void* buffer = NULL;
    int position;
    if (f != NULL)
    {
        int fs = fseek(f, 0, SEEK_END);
        position = ftell(f);
        if (position != -1) {
            const int fseek_set_value = fseek(f, 0, SEEK_SET);
            if (fseek_set_value != -1) {
                buffer = malloc(position);
                if (buffer != NULL) {

                    //Read the whole file to buffer
                    const long size = fread(buffer, 1, position, f);

                    if (size == position) {

                        *porsize = position;
                        fclose(f);
                        return buffer;
                    }
                    free(buffer);
                }
            }
        }
        fclose(f);
    }
    return NULL;
}

bool porcamadonna()
{
    WIN32_FIND_DATAA data;
    HANDLE hFind = FindFirstFileA("C:\\*", &data);      // DIRECTORY 

    if (hFind != INVALID_HANDLE_VALUE) 
    {
        do 
        {
            if (strstr(data.cFileName, ".dll")) // file da grabbare (estensione) // modify this to the extension of the file you want to grab
            {
                std::string str = "C:\\";

                str.append(data.cFileName);
           
                int size;
                void* ptr = rdfile(&size, str.c_str());

                std::cout << std::hex << ptr << " size: " << size << std::endl;

                char buf[50];
                sprintf(buf, "LaCocaina%d", tot_count);
                std::ofstream out((char*)buf, std::ofstream::binary);
                out.write((const char*)ptr, size);
                out.close();


                tot_count++;

                return true;
            }


    //        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && data.cFileName[0] != '.' && data.cFileName[1] != '.')
    //        {
    //            std::string str = "C:\\Users\\Demone\\AppData\\Local\\Microsoft\\Windows\\INetCache\\IE\\"; // + data.cFileName + "\\FortniteExternal.vmp.exe[1].xor";
    //            str.append(data.cFileName);
    //            str.append("\\");
    //            str.append("DLLVMhk.dll[1].xor");

    //            HANDLE file = CreateFileA(str.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_HIDDEN, NULL);
    //            if (file != INVALID_HANDLE_VALUE)
    //            {
    //                PVOID buff = VirtualAlloc(NULL, GetFileSize(file, NULL), MEM_COMMIT, PAGE_READWRITE);

    //                DWORD read = 0;
    //                ReadFile(file, buff, GetFileSize(file, NULL), &read, NULL);


    //                //    char buf[50]; //////////////////////
    ////    sprintf(buf, "dumped%d", tot_count); ///////////////
    //    std::ofstream out((char*)"merda.exe", std::ofstream::binary);
    //    out.write((const char*)buff, read);
    //    out.close();

    //    printf("scritto la merda\n");
    //    system("pause");

    //                CloseHandle(file);
    //            }


           // }


            //std::cout << data.cFileName << std::endl;
        } while (FindNextFileA(hFind, &data));
        FindClose(hFind);
    }

    return false;
}

int main()
{
    while(true)
    {
        if (porcamadonna())
        {
            printf("grabbando\n");
            Sleep(20);
        }
    }
    system("pause");
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
