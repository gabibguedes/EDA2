from tkinter import *
def merge(list_a, list_b):
    result = []
    a=0
    b=0
    invertions = 0
    
    while a < len(list_a) and b < len(list_b):

        if list_a[a] < list_b[b]:
            result.append(list_a[a])
            a = a + 1
        elif list_a[a] > list_b[b]:
            result.append(list_b[b])
            
            b = b + 1
            invertions += len(list_a) - a
    
    while a < len(list_a):
        result.append(list_a[a])
        a += 1
    
    while b < len(list_b):
        result.append(list_b[b])
        b+=1

    return result, invertions            

def count_invertions(list):
    if len(list) == 1:
        return list, 0
    
    half = int(len(list)/2)
 
    list_left, invertions_left = count_invertions(list[:half])
    list_right, invertions_right = count_invertions(list[half:])
    
    result, invertions = merge(list_left, list_right)
   
    invertions = invertions + invertions_left + invertions_right
 
    return result, invertions

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

def add():
    try:
        vector.append(float(element_e.get()))
    except:
        ERROR = 'ERRO: Valor inválido'
        listbox.config(fg='red')
        listbox.insert(0,ERROR)
    element_e.delete(0,'end')

def calc():

    vec, num = count_invertions(vector)  
                                  
    print(vector)                        
    print(num)                   
    
    result = []
    result.append('Vetor inicial: ' + str(vector))
    result.append('Vetor resultante: '+ str(vec))
    result.append('Número de inversões: '+str(num))
     
    for text in result:
        listbox.insert(END, text)

if __name__ == '__main__':
    vector = []
    app = Tk()
    app.title('Contando Inversões')
    app.geometry('500x400')
    app.resizable(0,0)

    back = Frame(master=app, bg='black')
    back.pack_propagate(0)
    back.pack(fill=BOTH, expand=1)

    title =  Label(back, text = 'Contador de Inversões', bg='black', fg='white')
    title['font'] = ('URW Gothic','14','bold')
    title.pack(fill=X, ipady=10)

    element_e = set_entry(back, 'Elemento do Vetor:', 30)
    
    button_widget = Frame(master=back, bg='black')
    button_widget.pack(fill=X, pady=20, padx=10)
    add_b = Button(button_widget, text='Adicionar ao vetor',pady=5, width=100,
                 command=add, bg='white', fg='black')
    add_b.pack()

    button2_widget = Frame(master=back, bg='black')
    button2_widget.pack(fill=X, pady=20, padx=10)
    enter = Button(button_widget, text='Calcular',pady=5, width=100,
                 command=calc, bg='white', fg='black')
    enter.pack()
    

    listbox = Listbox(back, bg='black', fg='white')
    listbox.pack(fill=BOTH, expand=1, pady=10, padx=10)
    
    app.mainloop()
 
