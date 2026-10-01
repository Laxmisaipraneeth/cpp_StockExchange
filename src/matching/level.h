/*
@file level.h
@brief Represents a discrete price level in the limit order book.

This header defines the structure for a specific price point, aggregating all 
resting orders at that price. It manages a FIFO (First-In, First-Out) queue 
via an intrusive doubly-linked list, ensuring constant-time order insertion 
and removal.

By maintaining internal pointers to the head and tail, the structure allows for 
rapid traversal and updates to order priority. It is designed for zero-allocation 
lifecycle management, working in tandem with memory pools to achieve deterministic 
performance during high-frequency matching operations.*/

#pragma once

#include <matching/order.h>
namespace exchange::matching {

    struct alignas(64) Level{
        core::Price price{0};
        core::Quantity total_qty{0};
        std::uint32_t order_count{0};
        Order *head{nullptr};
        Order *tail{nullptr};

        void add_order(Order *order) noexcept{
    
            order->prev = tail;
            order->next = nullptr;
            order->parent_level = this;
            if(tail!=nullptr){
                tail->next = order;
            }else{
                head = order;
            }
            tail = order;

            total_qty+= order->display_qty;
            ++order_count;
        }

        void remove_order(Order *order) noexcept{
            if(order->prev!=nullptr){
                order->prev->next = order->next;
            }else{
                head = order->next;
            }

            if(order->next!=nullptr){
                order->next->prev = order->prev;
            }else{
                tail = order->prev;
            }

            total_qty-=order->display_qty;
            --order_count;

            order->prev = nullptr;
            order->next = nullptr;
            order->parent_level = nullptr;
        }

        [[nodiscard]] Order *front() const noexcept {return head; }

        [[nodiscard]] bool is_empty() const noexcept { return head == nullptr;}

    };

}
