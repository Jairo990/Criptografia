import os

def procesar_texto(ruta_entrada, ruta_salida, desplazamiento, modo='cifrar'):
    if not os.path.exists(ruta_entrada):
        return False, "Error al abrir el archivo de la canción"

    if modo == 'descifrar':
        desplazamiento = -desplazamiento

    try:
        with open(ruta_entrada, "r", encoding="utf-8") as fp, \
             open(ruta_salida, "w", encoding="utf-8") as enc:
            
            for linea in fp:
                for c in linea:
                    if c.isupper():
                        base = ord('A')
                        encrypted_char = chr((ord(c) - base + desplazamiento) % 26 + base)
                        enc.write(encrypted_char)
                    
                    elif c.islower():
                        base = ord('a')
                        encrypted_char = chr((ord(c) - base + desplazamiento) % 26 + base)
                        enc.write(encrypted_char)
                    
                    else:
                        enc.write(c)

        return True, f"Tarea terminada."

    except Exception as e:
        return False, f'Error: {e}'