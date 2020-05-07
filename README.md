# Collection of functions for PostgreSQL


## Motivation

Simplify transition from Oracle to Postgres - set of useful Oracle functions re-implemented for Postgres. Also some additional helpful function.

This extension is for that.

## Examples

```sql
select is luhn('4000000000000002');
```
```
 isluhn
--------
      1
(1 row)
```
```sql
select luhnval('400000000000000');
```
```
 luhnval
---------
       2
(1 row)
```

```sql
select nvl(null,'x');
```
```
 nvl
-----
 x
(1 row)
```
