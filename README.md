# Warehouse Simulation

## Motivation

Warehouse operations involve multiple stages—picking, quality checking, packing, and shipping—each with limited workers. Poor resource allocation leads to bottlenecks, idle workers, and delayed orders. This simulation helps analyze how orders flow through a warehouse and identifies where inefficiencies occur.

## What This Simulation Does

Models a discrete-event warehouse with:

- **4 processing stages:** Picking → Quality Check → Packing → Shipping
- **Configurable workers** at each stage
- **Order priority system** (HIGH/NORMAL) with price-based tie-breaking for shipping
- **Queue management** when workers are busy

## KPIs Tracked

| KPI                       | What It Measures                       | Why It Matters                                          |
| ------------------------- | -------------------------------------- | ------------------------------------------------------- |
| **Worker Utilization %**  | Time workers are busy vs idle          | Low utilization = overstaffed, high = potential burnout |
| **Max Queue Length**      | Peak orders waiting at each stage      | Identifies bottleneck stages                            |
| **Average Wait Time**     | How long orders wait before processing | Directly impacts order fulfillment speed                |
| **Total Completion Time** | Time to process all orders             | Overall throughput measure                              |

## How It Helps

1. **Find Bottlenecks:** Max queue length shows which stage slows everything down
2. **Right-size Staff:** Utilization % reveals over/under-staffed stages
3. **Priority Handling:** HIGH priority orders get shipping preference, with higher-priced orders processed first when priorities match

## Build & Run

```bash
bash build.sh
```

Or manually:

```bash
cd src
g++ -o warehouse main.cpp Event.cpp Order.cpp Simulation.cpp
./warehouse input.txt
```

## Input Format

```
<pickers> <quality_checkers> <packers> <shippers>
<number_of_orders>
<arrival_time> <picking_time> <packing_time> <qc_time> <shipping_time> <price> <priority>
...
```

Priority: 0 = NORMAL, 1 = HIGH
