#include <stdio.h>
#include <stdint.h>

//Initialize Macro
#define CHECK_ITEMS_IN_CART(ShoppingCart, order) (ShoppingCart & (1 << order))

//Initialize Constant
typedef enum{
    SHIRT       = 1 << 0,   //0b00000001
    PANTS       = 1 << 1,   //0b00000010
    SKIRT       = 1 << 2,   //0b00000100
    DRESS       = 1 << 3,   //0b00001000
    RING        = 1 << 4,   //0b00010000
    BRACELET    = 1 << 5,   //0b00100000
    SHOES       = 1 << 6,   //0b01000000
    BAG         = 1 << 7    //0b10000000
}PersonalItems;

const uint8_t *listPersonalItems[] = {"SHIRT", "PANTS", "SKIRT", "DRESS", "RING", "BRACELET", "SHOES", "BAG"};

//Initialize Function
void add_to_shopping_cart(uint8_t *ShopingCart, PersonalItems Items);
void remove_from_shopping_cart(uint8_t *ShopingCart, PersonalItems Items);
void show_shopping_cart(uint8_t ShoppingCart);
void find_shopping_cart(uint8_t ShoppingCart, PersonalItems Items);

void main(){
    uint8_t ShoppingCart;

    add_to_shopping_cart(&ShoppingCart, SHIRT|SHOES|BAG);
    show_shopping_cart(ShoppingCart);
    remove_from_shopping_cart(&ShoppingCart, BAG);
    find_shopping_cart(ShoppingCart, BAG|RING|SHOES);
}

void add_to_shopping_cart(uint8_t *ShopingCart, PersonalItems Items){
    *ShopingCart |= Items;
}

void remove_from_shopping_cart(uint8_t *ShopingCart, PersonalItems Items){
    *ShopingCart &= ~Items;
}

void show_shopping_cart(uint8_t ShoppingCart){
    printf("\nShopping cart has: ");
    for(int i = 0; i<8; i++){
        if(CHECK_ITEMS_IN_CART(ShoppingCart, i)){
            printf("%s, ", listPersonalItems[i]);
        }
    }
}

void find_shopping_cart(uint8_t ShoppingCart, PersonalItems Items){
    for(int i = 0; i<8; i++){
        //Check each bit in Items from right to left
        if(Items & 1){
            if(CHECK_ITEMS_IN_CART(ShoppingCart, i)){
                printf("\nShopping cart has %s", listPersonalItems[i]);
            }
            else{
                printf("\nShopping cart doesn't have %s", listPersonalItems[i]);
            }
        }
        Items = Items >> 1;
    }
}