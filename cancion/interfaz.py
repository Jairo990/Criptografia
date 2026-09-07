import tkinter as tk
from tkinter import filedialog, messagebox

import song 

def seleccionar_archivo():
    ruta = filedialog.askopenfilename(filetypes=[("Archivos de Texto", "*.txt")])
    if ruta:
        entrada_ruta.delete(0, tk.END)
        entrada_ruta.insert(0, ruta)

def iniciar_proceso(modo):
    ruta_in = entrada_ruta.get()
    desplazamiento_str = entrada_desplazamiento.get()

    if not ruta_in:
        messagebox.showwarning("Atención", "Por favor selecciona un archivo de texto.")
        return
    
    try:
        desplazamiento = int(desplazamiento_str)
    except ValueError:
        messagebox.showerror("Error", 'Valor no aceptao')
        return

    if modo == 'cifrar':
        ruta_out = ruta_in.replace('.txt', '_c.txt')
    else:
        ruta_out = ruta_in.replace('.txt', '_d.txt')

    exito, mensaje = song.procesar_texto(ruta_in, ruta_out, desplazamiento, modo)

    if exito:
        messagebox.showinfo("Éxito", mensaje)
    else:
        messagebox.showerror("Error", mensaje)

ventana = tk.Tk()
ventana.title("Cifrador/Descifrador de Texto")
ventana.geometry("450x200")

tk.Label(ventana, text="Selecciona el archivo de texto (.txt):").pack(pady=5)

frame_archivo = tk.Frame(ventana)
frame_archivo.pack()
entrada_ruta = tk.Entry(frame_archivo, width=40)
entrada_ruta.pack(side=tk.LEFT, padx=5)
tk.Button(frame_archivo, text="Buscar", command=seleccionar_archivo).pack(side=tk.LEFT)

tk.Label(ventana, text="Nivel de desplazamiento (número):").pack(pady=5)
entrada_desplazamiento = tk.Entry(ventana, width=10)
entrada_desplazamiento.pack()

frame_botones = tk.Frame(ventana)
frame_botones.pack(pady=20)

tk.Button(frame_botones, text="Cifrar Texto", bg="lightblue", width=15, 
          command=lambda: iniciar_proceso("cifrar")).pack(side=tk.LEFT, padx=10)

tk.Button(frame_botones, text="Descifrar Texto", bg="lightgreen", width=15, 
          command=lambda: iniciar_proceso("descifrar")).pack(side=tk.LEFT, padx=10)

ventana.mainloop()