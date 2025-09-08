# Recursive Subset Sum Trace

**Set**: `[1, 2, 3]`, **Target**: `3`

## Visual Decision Tree (Vertical Layout)

```
Start: index=0, sum=0, subset=[]
│
├─ Include 1? YES
│  │
│  ├─ index=1, sum=1, subset=[1]
│  │  │
│  │  ├─ Include 2? YES
│  │  │  │
│  │  │  ├─ index=2, sum=3, subset=[1,2]
│  │  │  │  │
│  │  │  │  └─ sum==3 ✅ PRINT [1,2]
│  │  │  
│  │  └─ Include 2? NO
│  │     │
│  │     ├─ index=2, sum=1, subset=[1]
│  │     │  │
│  │     │  ├─ Include 3? YES
│  │     │  │  │
│  │     │  │  └─ index=3, sum=4, subset=[1,3]
│  │     │  │     │
│  │     │  │     └─ sum>3 ❌ STOP
│  │     │  
│  │     │  └─ Include 3? NO
│  │     │     │
│  │     │     └─ index=3, sum=1, subset=[1]
│  │     │        │
│  │     │        └─ index>=3 ❌ STOP
│  
└─ Include 1? NO
   │
   ├─ index=1, sum=0, subset=[]
   │  │
   │  ├─ Include 2? YES
   │  │  │
   │  │  ├─ index=2, sum=2, subset=[2]
   │  │  │  │
   │  │  │  ├─ Include 3? YES
   │  │  │  │  │
   │  │  │  │  └─ index=3, sum=5, subset=[2,3]
   │  │  │  │     │
   │  │  │  │     └─ sum>3 ❌ STOP
   │  │  │  
   │  │  │  └─ Include 3? NO
   │  │  │     │
   │  │  │     └─ index=3, sum=2, subset=[2]
   │  │  │        │
   │  │  │        └─ index>=3 ❌ STOP
   │  │  
   │  └─ Include 2? NO
   │     │
   │     ├─ index=2, sum=0, subset=[]
   │     │  │
   │     │  ├─ Include 3? YES
   │     │  │  │
   │     │  │  └─ index=3, sum=3, subset=[3]
   │     │  │     │
   │     │  │     └─ sum==3 ✅ PRINT [3]
   │     │  
   │     │  └─ Include 3? NO
   │     │     │
   │     │     └─ index=3, sum=0, subset=[]
   │     │        │
   │     │        └─ index>=3 ❌ STOP
```

## Step-by-Step Execution

### Call 1: `find_subsets(set, 3, subset, 0, 0, 0, 3)`
- **Current state**: index=0 (looking at '1'), sum=0, subset=[]
- **Decision**: Should I include element at index 0 (which is '1')?
- **Action**: Try both options

### Call 2: `find_subsets(set, 3, subset, 1, 1, 1, 3)` [Include 1]
- **Current state**: index=1 (looking at '2'), sum=1, subset=[1]
- **Decision**: Should I include element at index 1 (which is '2')?
- **Action**: Try both options

### Call 3: `find_subsets(set, 3, subset, 2, 2, 3, 3)` [Include 1, Include 2]
- **Current state**: index=2 (looking at '3'), sum=3, subset=[1,2]
- **Check**: sum == target_sum (3) ✅
- **Action**: **PRINT [1, 2]** and return

### Call 4: `find_subsets(set, 3, subset, 1, 2, 1, 3)` [Include 1, Don't include 2]
- **Current state**: index=2 (looking at '3'), sum=1, subset=[1]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 5: `find_subsets(set, 3, subset, 2, 3, 4, 3)` [Include 1, Don't include 2, Include 3]
- **Current state**: index=3, sum=4, subset=[1,3]
- **Check**: sum > target_sum (4 > 3) ❌
- **Action**: Return (stop this path)

### Call 6: `find_subsets(set, 3, subset, 1, 3, 1, 3)` [Include 1, Don't include 2, Don't include 3]
- **Current state**: index=3, sum=1, subset=[1]
- **Check**: index >= set_size (3 >= 3) ❌
- **Action**: Return (no more elements)

### Call 7: `find_subsets(set, 3, subset, 0, 1, 0, 3)` [Don't include 1]
- **Current state**: index=1 (looking at '2'), sum=0, subset=[]
- **Decision**: Should I include element at index 1 (which is '2')?
- **Action**: Try both options

### Call 8: `find_subsets(set, 3, subset, 1, 2, 2, 3)` [Don't include 1, Include 2]
- **Current state**: index=2 (looking at '3'), sum=2, subset=[2]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 9: `find_subsets(set, 3, subset, 2, 3, 5, 3)` [Don't include 1, Include 2, Include 3]
- **Current state**: index=3, sum=5, subset=[2,3]
- **Check**: sum > target_sum (5 > 3) ❌
- **Action**: Return (stop this path)

### Call 10: `find_subsets(set, 3, subset, 1, 3, 2, 3)` [Don't include 1, Include 2, Don't include 3]
- **Current state**: index=3, sum=2, subset=[2]
- **Check**: index >= set_size ❌
- **Action**: Return

### Call 11: `find_subsets(set, 3, subset, 0, 2, 0, 3)` [Don't include 1, Don't include 2]
- **Current state**: index=2 (looking at '3'), sum=0, subset=[]
- **Decision**: Should I include element at index 2 (which is '3')?
- **Action**: Try both options

### Call 12: `find_subsets(set, 3, subset, 1, 3, 3, 3)` [Don't include 1, Don't include 2, Include 3]
- **Current state**: index=3, sum=3, subset=[3]
- **Check**: sum == target_sum (3) ✅
- **Action**: **PRINT [3]** and return

### Call 13: `find_subsets(set, 3, subset, 0, 3, 0, 3)` [Don't include 1, Don't include 2, Don't include 3]
- **Current state**: index=3, sum=0, subset=[]
- **Check**: index >= set_size ❌
- **Action**: Return

## Final Output
```
[1, 2]
[3]
```

## Key Pattern
Notice how the recursion **explores every possible combination**:
- [1,2,3] → sum=6 (too big)
- [1,2] → sum=3 ✅
- [1,3] → sum=4 (too big) 
- [1] → sum=1 (too small)
- [2,3] → sum=5 (too big)
- [2] → sum=2 (too small)
- [3] → sum=3 ✅
- [] → sum=0 (too small)

The recursion naturally generates all 2³ = 8 possible subsets and checks each one!




Call 1: find_subsets(set=[1,2,2], subset=[], subset_size=0, start_index=0, target=4)
│ current_sum = 0, 0 < 4, continue exploring
│
├─ Loop i=0: Try element set[0] = 1
│  │ Check condition: i=0, start_index=0, so i > start_index? NO → Proceed
│  │ subset[0] = 1 → subset=[1]
│  └─ Call 2: find_subsets(subset=[1], subset_size=1, start_index=1, target=4)
│     │ current_sum = 1, 1 < 4, continue exploring
│     │
│     ├─ Loop i=1: Try element set[1] = 2 (first 2)
│     │  │ Check condition: i=1, start_index=1, so i > start_index? NO → Proceed
│     │  │ subset[1] = 2 → subset=[1,2]
│     │  └─ Call 3: find_subsets(subset=[1,2], subset_size=2, start_index=2, target=4)
│     │     │ current_sum = 3, 3 < 4, continue exploring
│     │     │
│     │     └─ Loop i=2: Try element set[2] = 2 (second 2)
│     │        │ Check condition: i=2, start_index=2, so i > start_index? NO → Proceed
│     │        │ subset[2] = 2 → subset=[1,2,2]
│     │        └─ Call 4: find_subsets(subset=[1,2,2], subset_size=3, start_index=3, target=4)
│     │           │ current_sum = 5, 5 > 4, STOP
│     │
│     └─ Loop i=2: Try element set[2] = 2 (second 2)
│        │ Check condition: i=2, start_index=1, so i > start_index? YES
│        │ Check condition: set[2] == set[1]? (2 == 2) YES
│        │ 🚫 SKIP THIS ITERATION (continue) ← DUPLICATE PREVENTION!
│
├─ Loop i=1: Try element set[1] = 2 (first 2)
│  │ Check condition: i=1, start_index=0, so i > start_index? YES
│  │ Check condition: set[1] == set[0]? (2 == 1) NO → Proceed
│  │ subset[0] = 2 → subset=[2]
│  └─ Call 5: find_subsets(subset=[2], subset_size=1, start_index=2, target=4)
│     │ current_sum = 2, 2 < 4, continue exploring
│     │
│     └─ Loop i=2: Try element set[2] = 2 (second 2)
│        │ Check condition: i=2, start_index=2, so i > start_index? NO → Proceed
│        │ subset[1] = 2 → subset=[2,2]
│        └─ Call 6: find_subsets(subset=[2,2], subset_size=2, start_index=3, target=4)
│           │ current_sum = 4, 4 == 4 ✅ PRINT [2,2]
│
└─ Loop i=2: Try element set[2] = 2 (second 2)
   │ Check condition: i=2, start_index=0, so i > start_index? YES
   │ Check condition: set[2] == set[1]? (2 == 2) YES  
   │ 🚫 SKIP THIS ITERATION (continue) ← DUPLICATE PREVENTION!

OUTPUT: [2,2] (NO DUPLICATES!)