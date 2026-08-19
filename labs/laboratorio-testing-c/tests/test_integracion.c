#include <stdio.h>
#include "../src/carrito.h"
#include "minunit/minunit.h"

/*
 * Tests de integracion: verifican que las funciones trabajan bien
 * en combinacion, no de forma aislada.
 */

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE D — Escribir el test guiado (ver README.md, Parte 8)
 * ═══════════════════════════════════════════════════════════════════════════ */

void test_compra_con_descuento(){
    Carrito c;
    Producto pan={"Pan", 200, 3};
    Producto leche={"Leche", 350 ,2};
    carrito_agregar(&c,pan);
    carrito_agregar(&c,leche);
    ASSERT_IGUAL(1300,carrito_total(&c));
    ASSERT_IGUAL(1170,carrito_descuento(carrito_total(&c),10));
}

/* ═══════════════════════════════════════════════════════════════════════════
 *  PARTE E — Disenar un test propio (ver README.md, Parte 9)
 * ═══════════════════════════════════════════════════════════════════════════ */

void test_agregar_hasta_llenar(){
    Carrito c;
    carrito_init(&c);
    Producto p = {"Leche", 350, 1};
    while (c.cantidad<MAX_ITEMS){
        printf("\nAgrega producto %d:", c.cantidad);
        carrito_agregar(&c,p);
    }
    printf("\nVerificacion de conteo MAX_ITEMS\n");
    ASSERT_IGUAL(MAX_ITEMS,c.cantidad);
    printf("Intentando exceder el MAX\n");
    ASSERT_IGUAL(0,carrito_agregar(&c,p));
    ASSERT_IGUAL(MAX_ITEMS,c.cantidad);
}


/* ═══════════════════════════════════════════════════════════════════════════
 *  main
 * ═══════════════════════════════════════════════════════════════════════════ */

int main(void) {
    printf("=== Tests de integracion ===");
    /* Descomentar a medida que agregues las funciones: */
    test_compra_con_descuento();
    test_agregar_hasta_llenar();
    RESUMEN();
    return EXIT_CODE();
}
