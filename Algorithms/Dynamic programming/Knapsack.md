# Problem Statement

Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. You cannot break an item, either pick the complete item or don’t pick it (0/1 property).

# Algorithm

## Properties to form the Knapsack table

The solution is to build a table, called a Knapsack table (abbreviated ``k_tbl``), where:
* Column: Value from 0 to W (capacity), incremented by 1 of each column
* Row: Store all items along with the NULL item.

The **NULL item** is the item with no weight and no value, which is as the base condition to be referenced, calculated by other items.

The Knapsack table is constructed so that a cell with index ``k_tbl[_item_idx][_c_idx]`` has the max total value with the capacity of ``_c_idx`` with totally ``_item_idx + 1`` items (count the NULL item).

For example:
* capacity W is 7, MAX_WEIGHTS = 7; and TOTAL_ITEMS is ``5``
* Array ``w[TOTAL_ITEMS + 1]`` stores the weight of all items: {0, 3, 1, 3, 4, 2} (0 for NULL item)
* Array ``v[TOTAL_ITEMS + 1]`` stores the value of all items: {0, 2, 2, 4, 5, 3}  (0 for NULL item)

Cell ``k_tbl[1][3]`` stores the max total value with the capacity of ``3`` with totally 2 items (= 1 + 1), with the index from 0 to 1 from array ``v`` and ``w``. All items (_weight, _value) in cell k_tbl[1][3] are (0, 0) and (3, 2) (i.e item with index {0, 1})

Cell ``k_tbl[4][5]`` stores the max total value with the capacity of ``5`` with totally ``5`` items (= 4 + 1). All items in cell ``k_tbl[4][5]`` are (0, 0), (3, 2), (1, 2), (3, 4), (4, 5); i.e item with index {0, 1, 2, 3, 4}

So the max total value of the knapsack of capacity W is stored at cell ``k_tbl[TOTAL_ITEMS][MAX_WEIGHTS]``

**Note**: The order we arrange all itmes in the array ``v`` and ``w`` doesn't effect the final result.

## Form the Knapsack table

### First row for the first, i.e NULL item
We start with NULL item, as the very first item, aka **item 0**. As we start with "item", we start by filling the column value of each row (i.e item). As the 1st item is the NULL one whose weight and value are 0, ``k_tbl[0][0]`` to ``k_tbl[0][MAX_WEIGHTS]`` is 0. It means with the capacity of 0 and the value of 0, a knapsack can't store any value.

### Second row for the second item

After filling the first item/row, we move to the next time. At the 2nd row, we now have 2 items (0, 0), (3, 2). We then move from the capacity index ``_c_idx = 0`` to ``MAX_WEIGHTS`` to fill all values from k_tbl[1][0] to k_tbl[1][MAX_WEIGHTS]. The capacity index ``_c_idx`` is also the current capacity we use to measure the max total value based on total current items. E.g with ``_c_idx = 3`` at this 2nd row, k_tbl[1][3] is the max total value with the capacity of ``3`` of totally 2 items (0,0) and (3,2).

First item has the item weight is w[1] = 3 and value is v[1] = 2:
* ``k_tbl[1][0]``: As w[1] > _c_idx, so ``k_tbl[1][0] = 0``. That's because an item with the weight of 3 can't be put inside the knapsack with the capcity of 0.
* ``k_tbl[1][1]``: As w[1] = 3 > _c_idx = 1, so item (3, 1) (**index 1**, aka **item 1**) can't be put inside this knapsack with the capacity of _c_idx = 1. However, we now have totally 2 items (index {0, 1}), and item at index 1 can't be put into the knapsack, we will consider the item at index 0. As 0 can't be put into the knapsack, too, so ``k_tbl[1][1] = 0``
* ``k_tbl[1][2]``: Same logic with ``k_tbl[1][1]``, ``k_tbl[1][2] = 0``
* ``k_tbl[1][3]``: As w[1] = 3 == _c_idx = 3, so this item can be put inside this knapsack
* From ``k_tbl[1][4]`` to ``k_tbl[1][7]``: Same logic with ``k_tbl[1][3]``.

### Third row for the 3rd item

* ``k_tbl[2][0] = 0`` 
* ``k_tbl[2][1]``: As w[2] = 1 == _c_idx = 1, so item (1, 2) (**index 2**, aka **item 2**) can be put inside this knapsack with the capacity of _c_idx = 1. Please note that, at this capacity _c_idx, as we are appending a new item (index 2) to our current items with index {0, 1}. Also note that at this _c_idx = 1 with items {0, 1}, we have already found the max total value (``k_tbl[1][1]``). So we have to make sure if item 2, which we decide to put inside the knapsack is bigger than ``k_tbl[1][1]`` (the current max value of this knapsack _c_idx):
    * If v[2] > ``k_tbl[1][1]``, we will put item 2 into the knapsack. ``k_tbl[2][1]`` will then be ``v[2] = 2``
    * If v[2] < ``k_tbl[1][1]``, we will keep {0, 1} in the knapsack and won't put item 2 in.

    In this case ``k_tbl[2][1] = v[2]``

* ``k_tbl[2][2]``: As w[2] = 1 < _c_idx = 2, so item 2 can be put inside this knapsack. If putting item 2 to the knapsack, there is still ``_c_idx - w[2] = 1`` capacity left inside the knapsack. As ``k_tbl[1][1]`` (the 2nd row) has the max total value with the capacity of ``_c_idx = 1`` with totally 2 items {0, 1}, the total value can be put inside the knapsack now is: ``v[2] + k_tbl[1][1]``. With _item_idx is the current item index, _item_idx = 2 in this case, the general formular will be: ``v[_item_idx] + k_tbl[_item_idx-1][_c_idx - w[_item_idx]]``

Apply same comparison logic of ``k_tbl[2][1]``, ``k_tbl[_item_idx][_c_idx]`` will be: 

```c
k_tbl[_item_idx][_c_idx] = MAX(k_tbl[_item_idx-1][_c_idx], v[_item_idx] + k_tbl[_item_idx-1][_c_idx - w[_item_idx]]);
```

``k_tbl[2][2] = 2``

Apply the same logic for the rest cells of the table.

# Find the items to select for the max value

To find the selected item, we track the Knapsack table backward, start at the bottom of the table, i.e at ``k_tbl[TOTAL_ITEMS][MAX_WEIGHTS]`` - the max total value, then move up until the NULL item. An item is chosen if its value ``k_tbl[_item_idx][_c_idx]`` and the value above it ``k_tbl[_item_idx-1][_c_idx]`` differ. That's because if the 2 values differed, then the row were currently on must have had its item include, otherwise the value would not have changed. After we choose that item, we substract the capacity index ``_c_idx`` by the weight of the chosen item, i.e ``_c_idx = _c_idx - w[_item_idx]``.

After deciding to choose or not to choose an item, simple move upward to check the next item. 

# Program

[knapsack.c](knapsack.c)
