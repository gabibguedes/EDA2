from tkinter import *
import numpy as np

## Global variables
current_element = 0
values = []
weights = []
k_weight = 0
num_elem = 0

label_1 = ''

def knapsack_solver(max_weight, weight_vector, value_vector):
    n_elements = len(value_vector)
    
    matrix = [[0 for x in range(max_weight+1)] for x in range(n_elements+1)] 

    for line in range(n_elements + 1):
        for column in range(max_weight + 1):
            if line == 0 or column == 0:
                matrix[line][column] = 0
            elif weight_vector[line -1] <= column:
                w = column - weight_vector[line -1]
                v = value_vector[line - 1] + matrix[line-1][w]
                matrix[line][column] = max(v, matrix[line-1][column])  
            else:
                matrix[line][column] = matrix[line-1][column]
    
    return matrix[n_elements][max_weight]
            

def set_entry(parent, label_text, width=None, **options):
    entry_widget = Frame(master=parent, bg='black')
    entry_widget.pack(fill=X, ipady= 10, padx=10)
    Label(entry_widget, text=label_text, bg='black', fg='white').pack(side=LEFT)
    entry = Entry(entry_widget, **options, bg='black', fg='white',
                insertbackground='white')
    if width:
        entry.config(width=width)
    entry.pack(side=RIGHT)
    return entry

def save_knapsack_weight():
    global num_elem
    global k_weight
    global label_1, element_value, element_weight, go, listbox
    global current_element
    
    listbox = Listbox(back, bg='black', fg='white') 

    try: 
        k_weight = int(knapsack_weight.get())
        num_elem = int(num_elements.get())
    except:
        print('erro1')
        ERROR = 'ERRO: Valor inválido'
        print(ERROR)
        listbox.config(fg='red')
        listbox.insert(0,ERROR)
     
    label_1 = StringVar()
    label_1.set('') 
    num_element = Label(back, textvariable = label_1 , bg='black', fg='white').pack()
    element_value = set_entry(back, 'Valor:', 30)
    element_weight = set_entry(back, 'Peso:', 30)
    
    if current_element < num_elem:
        button_widget = Frame(master=back, bg='black')
        button_widget.pack(fill=X, pady=20, padx=10)
        go = Button(button_widget, text='Adicionar Elemento',pady=5, width=100,
                    command=add_values, bg='white', fg='black')
        go.pack()
    
    listbox.pack(fill=BOTH, expand=1, pady=10, padx=10)
    
    update()

def add_values():
    global values, weights, element_value, element_weight, listbox

    try:
        v = int(element_value.get())
        w = int(element_weight.get())
        values.append(v)
        weights.append(w)
        update()
    except:
        print('erro2')
        ERROR = 'ERRO: Valor inválido'    
        print(ERROR)                      
        listbox.config(fg='red')          
        listbox.insert(0,ERROR)           
        

def update():    
    global current_element, num_elem
    global label_1, go
    
    current_element += 1
    
    element_value.delete(0,'end')
    element_weight.delete(0,'end')

    label_1.set('Elemento ' + str(current_element))

    if current_element >= num_elem:
        go.config(text='Calcular',command=calc)
    
def calc():
    global values, weights, current_element, num_elem, k_weight
    try:                                      
        v = int(element_value.get())        
        w = int(element_weight.get())       
        values.append(v)                      
        weights.append(w)                     
   
    except:                                   
        print('erro2')                        
        ERROR = 'ERRO: Valor inválido'        
        print(ERROR)                          
        listbox.config(fg='red')              
        listbox.insert(0,ERROR)               

    result = knapsack_solver(k_weight, weights, values)
    result_text = 'A soma dos valores que cabem na mochila é ' + str(result)
    listbox.insert(0,result_text)

if __name__ == '__main__':
    app = Tk()

    app.title('Knapsack Problem')
    app.geometry('500x500')
    app.resizable(0,0)
    
    back = Frame(master=app, bg='black')
    back.pack_propagate(0)
    back.pack(fill=BOTH, expand=1)

    
    title =  Label(back, text = 'The Knapsack Problem Solver', bg='black',
                   fg='white')
    title['font'] = ('URW Gothic','14','bold')
    title.pack(fill=X, ipady=10)

    knapsack_weight = set_entry(back, 'Peso maximo da mochila:', 30)  
    num_elements = set_entry(back, 'Numero de elementos:', 30)

    button_widget = Frame(master=back, bg='black')
    button_widget.pack(fill=X, pady=20, padx=10)
    fill = Button(button_widget, text='Preencher valores e pesos',pady=5, width=100,
                command=save_knapsack_weight, bg='white', fg='black')
    fill.pack()
   
    
    
    app.mainloop()
