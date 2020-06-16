// C++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

using namespace std;

int main()
{
    //Auto-Explicativo
    DWORD procId = GetProcId(L"ProjectG.exe");

    //Auto-Explicativo
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ProjectG.exe");

    //Pegando o processo
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    
    //Endereço base para o point trabalhar.
    uintptr_t dynamicPtrBaseAddr = moduleBase + 0x007229D8; //valor de memoria certa 

    //Calculo para o point.
    std::vector<unsigned int> ammoOffsets = { 0x1C, 0x30, 0x10, 0x10, 0x18, 0x0, 0x24 }; //offsets errada propositalmente vera algumas varições as vezes
    uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

    float valorinicial = 0;
    float aux = 0;
    double resultado = 0;

    /*Estrutura de repetição basicamente o seguinte salvo o valor da distancia em um auxiliar e obtenho um novo
    valor da distancia e comparo novamente com a distancia sempre que forem diferentes ele refaz o calculo
    Obs: fiz assim pq estava com outra ideia mas desistio no meio do caminho*/
    ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &valorinicial, sizeof(aux), nullptr);
    do
    {
     ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &aux, sizeof(valorinicial), nullptr);
        if (aux != valorinicial)
        {
            resultado = (aux - valorinicial) / 1.056616; //valor da constante aproximado para 236y mais detalhes no proximo comentario
            std::cout << "PB: = " << std::dec << resultado << std::endl;
            system("cls");
        } 
    } while (true);
}
/*seguinte o valor (1.056616) e um valor aproximado para 236y para transformar o valor alocado na memoria em PB por exemplo se voce estiver a
70y do hole voce vera que o PB nao sera o mesmo do programa com a barra do pangya, ou valor correto é um variavel e não um constante
utilizando trigonometria basica voce consegue descobrir essa variavel com apenas 3 pontos se não souber usar trigonometria basica
pode utilizar regra de 3 tbm se aplica porem sera necessarios mais de 10 pontos para um precisão boa*/