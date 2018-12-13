from random import *
import os
import time

def busca_sequencial_padrao(vetor,numero_desejado):
    start_time = time.time()
    for i in range(len(vetor)):
        if (vetor[i] == numero_desejado):
            elapsed_time = time.time() - start_time
            print('Tempo de busca sequencial padrao: ' + str(elapsed_time) + ' s' )
            return i
    elapsed_time = time.time() - start_time
    print('Tempo de busca sequencial padrao: ' + str(elapsed_time) + ' s' )
    return 'Valor nao encontrado!'

def busca_sequencial_sentinela(vetor,numero_desejado):
    start_time = time.time()
    vetor.append(numero_desejado)
    contador = 0
    while(numero_desejado != vetor[contador]):
        contador = contador + 1
    if(contador == len(vetor)-1):
        elapsed_time = time.time() - start_time
        print('Tempo de busca sequencial com sentinela: ' + str(elapsed_time))
        return 'Valor nao encontrado!'
    else:
        elapsed_time = time.time() - start_time
        print('Tempo de busca sequencial com sentinela: ' + str(elapsed_time) + ' s')
        return contador

def busca_binaria(vetor,numero_desejado):
    start_time = time.time()
    valor_inicial = 0
    valor_final = len(vetor)-1
    valor_medio = valor_final/2
    for i in range(len(vetor)):
        if(numero_desejado == vetor[valor_medio]):
            elapsed_time = time.time() - start_time
            print('Tempo de busca binaria: ' + str(elapsed_time) + ' s')
            return valor_medio
        elif(numero_desejado > vetor[valor_medio]):
            valor_inicial = valor_medio + 1
            valor_medio = valor_medio + 1 + (valor_final - valor_inicial)/2
        elif (numero_desejado < vetor[valor_medio]):
            valor_final = valor_medio - 1
            valor_medio = valor_medio - 1 -(valor_final - valor_inicial)/2
        else:
            elapsed_time = time.time() - start_time
            print('Tempo de busca binaria: ' + str(elapsed_time) + ' s')
            return 'Valor nao encontrado!'

def busca_interpolacao(vetor, numero_desejado):
    start_time = time.time()
    meio = ((len(vetor)-1) * (numero_desejado - vetor[0]))/(vetor[len(vetor)-1] - vetor[0])
    elapsed_time = time.time() - start_time
    print('Tempo de busca por interpolacao: ' + str(elapsed_time) + ' s')
    if vetor[meio] == numero_desejado:
        return meio
    else:
        return'Valor nao encontrado!'

def preenche_vetor_desordenado(vetor):
    for i in range(0,10):
       vetor.append(randint(0,100))

def preenche_vetor_ordenado(vetor):
    for i in range(0,10):
        vetor.append(i)

def menu():
    os.system('clear')
    print('================== MENU =================')
    print('')
    print('1 - Vetor desordenado: ' +str(vetor_desordenado))
    print('2 - Vetor ordenado: ' +str(vetor_ordenado))
    print('')
    opcao = input('Deseja fazer a busca em qual dos vetores? ')
    if(opcao == 1):
        buscar_vetor_desordenado()
    elif(opcao == 2):
        buscar_vetor_ordenado()
    else:
        print('Opcao Invalida!')
        time.sleep(3)
        menu()

def buscar_vetor_desordenado():
    os.system('clear')
    print('================== VALORES =================')
    print('')
    print('Vetor: ' +str(vetor_desordenado))
    print('')
    valor = input('Qual valor desejado? ')
    print('')
    posicao = busca_sequencial_padrao(vetor_desordenado,valor)
    busca_sequencial_sentinela(vetor_desordenado,valor)
    print('')
    print('A primeira ocorrencia do elemento foi na posicao: ' + str(posicao))

def buscar_vetor_ordenado():
    os.system('clear')
    print('================== VALORES =================')
    print('')
    print('Vetor: ' +str(vetor_ordenado))
    print('')
    valor = input('Qual valor desejado? ')
    print('')
    posicao = busca_sequencial_padrao(vetor_ordenado,valor)
    busca_sequencial_sentinela(vetor_ordenado,valor)
    busca_binaria(vetor_ordenado,valor)
    busca_interpolacao(vetor_ordenado, valor)
    print('')
    print('O elemento esta na posicao: ' + str(posicao))

vetor_desordenado = []
vetor_ordenado = []

preenche_vetor_desordenado(vetor_desordenado)
preenche_vetor_ordenado(vetor_ordenado)
menu()
