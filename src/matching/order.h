/*
@file order.h
@brief Defines the core order structure for the matching engine.

This header represents the fundamental data unit of the exchange. It encapsulates
all necessary attributes for various order types (limit, market, stop, etc.) in a
single, fixed-size structure to facilitate efficient memory management and
in-place mutation during the matching lifecycle.

To ensure low-latency performance and hardware cache efficiency, this structure is
trivially copyable and follows strict deterministic memory alignment, avoiding
virtual functions or dynamic dispatch to prevent vtable overhead and branching.
*/