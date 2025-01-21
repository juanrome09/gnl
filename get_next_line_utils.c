/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanrome <juanrome@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:15 by juanrome          #+#    #+#             */
/*   Updated: 2025/01/15 21:35:06 by juanrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main() {
    // Abre el archivo en modo de solo lectura
    int fd = open("archivo.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char buffer[100]; // Buffer para almacenar los datos leídos
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    
    if (bytesRead == -1) {
        perror("Error al leer el archivo");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0'; // Aseguramos que el buffer sea una cadena
    printf("Datos leídos:\n%s\n", buffer);

    // Cierra el descriptor de archivo
    close(fd);
    return 0;
}