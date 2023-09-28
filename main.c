#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>


/* compute the diff of cur from ref
    diff : 
*/
const size_t CHUNK_SIZE = 256; //? 256 char long chunks 

struct Diff { //? 256 char long chunks ?
    unsigned char start; // start affected part
    unsigned char type; // 0 : removed, 1 : added, 2 : replaced
    unsigned char * replacement; // NULL if removed
    size_t length; // in count of characters (if CHUNK_SIZE change between diff)
};
typedef struct Diff Diff;

struct Diffs {
    Diff * diffs;
    size_t count;
};
typedef struct Diffs Diffs;

struct LCS {
    unsigned char ** c;
    size_t ** c_len;
    size_t x_len;
    size_t y_len;
    // lcs = c[x_len][y_len]
    // lcs_len = c_len[x_len][y_len]
};

void lcs(unsigned char * x, unsigned char * y, size_t x_len, size_t y_len){
    c = calloc(x_len*y_len*sizeof(unsigned char *));
    c_len = calloc(x_len*y_len*sizeof(size_t));
    for(size_t i = 1; i<x_len; i++){
        for(size_t j = 1; j<y_len; j++){
            if(X[i] == Y[j]){
                c_len[i][j] = c_len[i-1][j-1] + 1;
                malloc(c[i][j], c_len[i][j]*sizeof(unsigned char));
                memcpy(c[i][j], c[i-1][j-1], c_len[i][j]*sizeof(unsigned char));
                c[i][j][c_len[i][j]-1] = X[i];
        }
    }
}

//absolutely not optimal
Diffs diff(unsigned char * old, size_t old_len, unsigned char * new, size_t new_len){
    size_t count = 0;
    size_t v_size = 1;
    Diff * diffs = malloc(v_size*sizeof(Diff));
    for(size_t i = 0; i<old_len; i++){
        if(old[i] != new[i]){ //there's a diff
            size_t j = i;
            for(; j<old_len && old[j] != new[j] ; start++);
            if(new[j] == old[i]){ // added
                Diff diff = {start, 0, NULL, j-start};
                diffs[count] = diff;
                count ++;
            }else{ // replaced
            Diff diff = {start, 2, new+start, i-start};
            diffs[count] = diff;
            count ++;
        }
    }

    for(size_t i = 0; i<ref_len; i++){
        if(i<cur_len){
            if(ref[i] != cur[i]){
                size_t start = i;
                for(; i<ref_len && ref[i] != cur[i] ; i++){
                }
                count ++;
            }
        }else{
            Diff diff = {i, ref_len-i, NULL};
            diffs[count] = diff;
            count ++;
        }
        if(v_size<count){ // expand array //? <= ?
            Diff * t_diffs = malloc(2*v_size*sizeof(Diff));
            memcpy(t_diffs, diffs, count);
            free(diffs);
            diffs = t_diffs;
            v_size *= 2;
        }
    }
    return (Diffs) {diffs, count};
}

struct Leaf {
    unsigned char * data;
    size_t size;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct Leaf * leafs;
    size_t length;
    size_t a_length;
};
typedef struct Leaf Leaf;

void printLeaf(Leaf * leaf){
    printf("Input : %s | hash : ", leaf->data);
    for(int i = 0; i<SHA256_DIGEST_LENGTH; i++){
        printf("%x", leaf->hash[i]);
    }
    printf("\n");
}


unsigned int log2shift(size_t n){
    unsigned int i = 0;
    while(n){
        n>>=1;
        i++;
    }
    return i-1;
}

char compareHash(unsigned char hash[SHA256_DIGEST_LENGTH], unsigned char hash2[SHA256_DIGEST_LENGTH]){
    for(size_t i = 0; i<SHA256_DIGEST_LENGTH; i++){
        if(hash[i] > hash2[i]) return 1;
        if(hash[i] < hash2[i]) return -1;
    }
    return 0;
}

size_t indexLeaf(unsigned char hash[SHA256_DIGEST_LENGTH], Leaf * leaf){// to check
    unsigned int max_it = log2shift(leaf->length);
    char match = 2;//...
    unsigned int j = 0;
    size_t li = 0;
    size_t hi = leaf->length;
    size_t i = 0;
    while(match && max_it>j){
        i = (li + hi)>>1;
        match = compareHash(hash, leaf->leafs[i].hash);
        if(match > 0) li = i;
        if(match < 0) hi = i;
        j++;
    }
    return i;
}

void addLeaf(Leaf leaf, Leaf * container){
    printLeaf(&leaf);
    if(container->length){
        if(container->a_length<=container->length+1){//! <= ?
            Leaf * t_leafs = malloc(2*container->a_length*sizeof(Leaf));
            memcpy(t_leafs, container->leafs, container->length);
            free(container->leafs);
            container->leafs = t_leafs;
            container->a_length *= 2;
        }
        size_t i = indexLeaf(container->hash, container);
        printf("passed %i\n", i);

        //memcpy(leaf->leafs, leaf->leafs, i);
        memcpy(container->leafs+i+1, container->leafs, container->length-i);
        container->leafs[i] = leaf;
    }else{
        if(!container->a_length){
            container->leafs = malloc(sizeof(Leaf));
        }
        container->leafs[0] = leaf;
        container->length++;
    }
}

void removeLeaf(unsigned char hash[SHA256_DIGEST_LENGTH], Leaf * leaf){
    //todo
}

Leaf head;


int main(int argc,char *argv[]){
    unsigned char * in = "Hello";
    unsigned char * hash = SHA256(in, strlen(in), NULL);
    Leaf leaf1 = (Leaf){in, strlen(in), hash, NULL, 0, 0};
    printLeaf(&leaf1);
    addLeaf(leaf1, &head);

    unsigned char * in2 = "Helloa";
    unsigned char * hash2 = SHA256(in2, strlen(in2), NULL);
    addLeaf((Leaf){in2, strlen(in2), hash2, NULL, 0, 0}, &head);

    unsigned char * in3 = "GHJoa";
    unsigned char * hash3 = SHA256(in3, strlen(in3), NULL);
    addLeaf((Leaf){in3, strlen(in3), hash3, NULL, 0, 0}, &head);
    return 0;
}

