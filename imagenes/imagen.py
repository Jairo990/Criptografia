import os

def procesar_imagen(ruta_entrada, ruta_salida, desplazamiento, modo ='cifrar'):
    if not os.path.exists(ruta_entrada):
        return False, 'Error'

    if modo == 'descifrar':
        desplazamiento = -desplazamiento
    
    # verificar existencia del archiv
    try:
        with open(ruta_entrada, "rb") as archivo:
            signature = archivo.read(2)
            if signature != b'BM':
                return False, 'Error: archivo no es un BMP'

            archivo.seek(2)
            file_size = int.from_bytes(archivo.read(4), byteorder='little')

            reserved = int.from_bytes(archivo.read(4), byteorder='little')

            offset = int.from_bytes(archivo.read(4), byteorder='little')  # little endian

            header_size = int.from_bytes(archivo.read(4), byteorder='little')

            width = int.from_bytes(archivo.read(4), byteorder='little')

            height = int.from_bytes(archivo.read(4), byteorder='little', signed = True)
            new_height = abs(height)
            
            planes = int.from_bytes(archivo.read(2), byteorder='little')

            bits_per_pixel = int.from_bytes(archivo.read(2), byteorder='little')

            compression = int.from_bytes(archivo.read(4), byteorder='little')

            image_size = int.from_bytes(archivo.read(4), byteorder='little')

            x_pixel_por_meter = int.from_bytes(archivo.read(4), byteorder='little')

            y_pixel_por_meter = int.from_bytes(archivo.read(4), byteorder='little')

            colors_used = int.from_bytes(archivo.read(4), byteorder='little')

            colors_important = int.from_bytes(archivo.read(4), byteorder='little')

            if bits_per_pixel != 24:
                return False, 'El archivo no es un BMP de 24 bits'

            padding = (4 - (width * 3) % 4) % 4

            archivo.seek(0)
            cabecera = archivo.read(offset)

            archivo.seek(offset)
            new_data = bytearray()
            pad_bytes = bytes([0] * padding)

            for i in range(new_height):
                for j in range(width):
                    pixel = archivo.read(3)
                    b, g, r = pixel[0], pixel[1], pixel[2]

                    new_b = (b + desplazamiento) % 256
                    new_g = (g + desplazamiento) % 256
                    new_r = (r + desplazamiento) % 256
                    new_data.extend([new_b, new_g, new_r])
                archivo.read(padding)
                new_data.extend(pad_bytes)

        with open(ruta_salida, "wb") as output:
            output.write(cabecera)
            output.write(new_data)

        return True, 'Imagen procesada'

    except Exception as e:
        return False, f'Error {e}'
