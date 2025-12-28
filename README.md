# Data Structures Visualizer

A data structures visualizer with core implementations written in C and a
Python-based visualization layer.

## Overview
This project implements core data structures in C with an emphasis on
clear ownership rules, correctness, and reusability. A generic linked
list forms the foundation for stacks, queues, and future data structures.

## Design Philosophy

All containers store generic `void *` payloads and manage only their
internal structure. Ownership of stored data remains with the caller, who 
is responsible for allocation and deallocation.

## Data Structures

- Generic linked list
- Stack (built on linked list)
- Queue (built on linked list)
- Hash table (chaining, in progress)

## Project Structure