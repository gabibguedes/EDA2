from random import *
import os
import time
import matplotlib.pyplot as plt

def quicksort(vector,min,max):
    pivo = getPivo(min,max)
    storeIndex = min
    aux = vector[max]
    vector[max] = vector[pivo]
    vector[pivo] = aux
    for i in range(min,max):
        if vector[i] < vector[max]:
            aux = vector[storeIndex]
            vector[storeIndex] = vector[i]
            vector[i] = aux
            storeIndex += 1
    aux = vector[max]
    vector[max] = vector[storeIndex]
    vector[storeIndex] = aux
    return storeIndex

def chama_quicksort(vector,start,end):
    if end > start:
        pos = quicksort(vector,start,end)
        chama_quicksort(vector,start,pos-1)
        chama_quicksort(vector,pos+1,end)

def getPivo(min,max):
    pivo = int((max-min)/2 + min)
    return pivo

def mergesort(vector, start, middle, end):
    vector_aux = []
    c_start = start
    c_mid = middle + 1
    ind = start

    while(ind <= end):
        if c_start > middle:
            vector_aux.append(vector[c_mid])
            c_mid += 1
        elif c_mid > end:
            vector_aux.append(vector[c_start])
            c_start +=1
        elif vector[c_start] < vector[c_mid]:
            vector_aux.append(vector[c_start])
            c_start += 1
        else:
            vector_aux.append(vector[c_mid])
            c_mid +=1
        ind += 1

    aux = 0
    for i in range(start, end + 1):
        vector[i] = vector_aux[aux]
        aux += 1

def chama_mergesort(vector, start, end):
    if start < end:
        middle = int((end + start)/2)
        chama_mergesort(vector, start, middle)
        chama_mergesort(vector, middle +1, end)
        mergesort(vector, start, middle, end)

def generate_vector(size, intervals):
    random_vector = []
    for i in range(size):
        new_element = randint(0,intervals)
        random_vector.append(new_element)
    return random_vector

def heapfy(vector,index):
    maior = index
    left = 2*index
    right = 2*index+1

    if(vector[0] >= right):
        if(vector[index] < vector[right]):
            maior = right
        if(vector[maior] < vector[left]):
            maior = left
        if(maior != index):
            vector[maior],vector[index] = vector[index],vector[maior]
            heapfy(vector,maior)
    elif(vector[0] >= left): 
        if(vector[index] < vector[left]):
            vector[left],vector[index] = vector[index],vector[left]
            heapfy(vector,left)

def buildHeap(vector):
    vector = [len(vector)] + vector
    for i in range(int(len(vector)/2),0,-1):
        heapfy(vector,i)
    # print(vector)
    return vector

def heapsort(vector):
    vector = buildHeap(vector)
    for i in range(len(vector)-1,0,-1):
        vector[1], vector[i] = vector[i] , vector[1]
        vector[0] -= 1
        heapfy(vector,1)
    vector.pop(0)

def calc_time_quicksort(smaller, bigger,x):
    times = []
    values = []
    for i in range(smaller,bigger,x):
        start_time = time.time()
        vec = generate_vector(i, 10*i)
        chama_quicksort(vec,0,len(vec)-1) 
        elapsed_time = time.time() - start_time
        times.append(elapsed_time)
        values.append(i)
    call_new_plot(times, values)

def calc_time_mergesort(smaller, bigger,x):
    times = []
    values = []
    for i in range(smaller,bigger,x):
        start_time = time.time()
        vec = generate_vector(i, 10*i)
        chama_mergesort(vec,0,len(vec)-1) 
        elapsed_time = time.time() - start_time
        times.append(elapsed_time)
        values.append(i)
    call_new_plot(times, values)


def calc_time_heapsort(smaller, bigger, x):
    times = []
    values = []
    for i in range(smaller,bigger,x):
        start_time = time.time()
        vec = generate_vector(i, 10*i)
        heapsort(vec) 
        elapsed_time = time.time() - start_time
        times.append(elapsed_time)
        values.append(i)
    call_new_plot(times, values)

def call_new_plot(times, value):
    plt.plot(value, times)
               

def plot_grafic(s,b):
    legends = ['quicksort', 'mergesort', 'heapsort']
    
    i = 1
    if b >= 10000000:
        i = b
    elif b >= 1000000:
        i = 10000
    elif b >= 100000:
        i = 1000
    elif b >= 10000:
        i = 100
    elif b >= 1000:
        i = 10
    
    calc_time_quicksort(s,b,i)
    calc_time_mergesort(s,b,i)
    calc_time_heapsort(s,b,i)
    plt.title('Gráfico de Algorítimos de Ordenação')
    plt.xlabel('Quantidade de elementos no vetor')
    plt.ylabel('Tempo de ordenação')
    plt.grid(True)
    plt.legend(legends)
    plt.show()


os.system('clear')
print('Escolha o tamanho dos vetores para os gráficos:')
smaller = int(input('Menor vetor: '))
bigger = int(input('Maior vetor: '))
print('Aguarde um instante, seu gráfico está sendo montado')
plot_grafic(smaller, bigger)
