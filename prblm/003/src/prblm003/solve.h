//
//  solve.h
//  prblm003
//
//  Created by Himari Takakura on 3/30/20.
//  Copyright © 2020 Himari Takakura. All rights reserved.
//

#ifndef solve_h
#define solve_h

//#define SLIDING_WINDOW
//#define BRUTE_FORCE
#define SLIDING_WINDOW_OPTIMUM


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

static inline void str_print(char *str, uint32_t len){
    
    if(len <= 0) return;
    for(uint32_t i = 0; i<len; i++){
        printf("%c", str[i]);
    }
    printf("\n");
    
}

static inline int str_is_contain(char c, char *str, uint32_t len){
    
    if(len <= 0) return 0;
    for(uint32_t i=0; i<len; i++){
        if(c == str[i])
            return 1;
    }
    return 0;
    
}

static inline int each_char_is_unique(char *str, uint32_t len){
    
    if(len <= 0) return 0;
    for(uint32_t i = 1; i<len; i++){
        if( str_is_contain(str[i], str, i) )
            return 0;
    }
    return 1;
    
}

static inline int __pri_strrchr(char c, char *str, uint32_t start, uint32_t end){
    if((start > end) || (start < 0)) return -1;
    
    for(int i = end; i >= (int)start; i--){
        if(str[i] == c){
            return i;
        }
    }
    return -1;
}

// answer 1
int brute_force(char *str, uint32_t len){
    
    if(len <= 0) return 0;
    if(len == 1) return 1;
    
    uint32_t head;
    uint32_t tail;
    
    uint32_t ret = 1;
    
    for(head = 0; head < len-1; head++){
        for(tail = head + 1; tail < len; tail++){
            uint32_t tmp = tail - head + 1;
            if(each_char_is_unique(&str[head],tmp))
                ret = (ret>tmp)?ret:tmp;
        }
    }
    
    return ret;
}

// answer 2
int sliding_window(char *str, uint32_t len){
    
    if(len <= 0) return 0;
    if(len == 1) return 1;
    
    uint32_t head = 0;
    uint32_t tail = 0;
    
    uint32_t ret = 0;
    
    while((head < len) && (tail < len)){
        if(!str_is_contain(str[tail], &str[head], tail - head)){
            tail++;
            ret = (ret>(tail-head))?ret:(tail-head);
        }
        else{
            head++;
        }
    }
    
    return ret;
}

// answer 3
int sliding_window_optimum(char *str, uint32_t len){
    if(len <= 0) return 0;
    if(len == 1) return 1;
    
    uint32_t head = 0;
    uint32_t tail = 1;
    
    uint32_t ret = 0;
    
    while ((tail < len) && (head < len)) {
        int tmp = __pri_strrchr(str[tail], str, head, tail-1);
        
        if(tmp != -1)
            head = (uint32_t)tmp + 1;
        
        ret = (ret>(tail-head+1))?ret:(tail-head+1);
        tail++;
    }
    
    return ret;
}

int lengthOfLongestSubstring(char * s){
#ifdef BRUTE_FORCE
    return brute_force(s, (uint32_t)strlen(s));
#endif

#ifdef SLIDING_WINDOW
    return sliding_window(s, (uint32_t)strlen(s));
#endif
    
#ifdef SLIDING_WINDOW_OPTIMUM
    return sliding_window_optimum(s, (uint32_t)strlen(s));
#endif
    return 0;
}

#endif /* solve_h */
