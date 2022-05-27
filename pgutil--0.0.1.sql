--create function nvl(text, text) returns text as '$libdir/nvl' language C immutable;

create function sdecode(VARIADIC args text[]) returns text as '$libdir/decode' language C immutable strict;
create function isluhn(num text) returns int as '$libdir/luhn' language C immutable strict;
create function luhnval(num text) returns int as '$libdir/luhn' language C immutable strict;
create function mapcount(tname text) returns int as '$libdir/luhn' language C immutable strict;

/*~
create function idecode(VARIADIC args int[]) returns int language plpgsql immutable strict as $$
declare
 i int;
 v1 int;
 N int;
 defval int := null;
begin
 --raise notice 'p0=%', args[1];
 N := array_length(args,1);
 if N%2=0 then -- last element represents default value
   defval := args[N];
   --raise notice 'defval = %', defval;
   N := N - 1;
 end if;
 for i in 2..N loop
  if i%2=0 then v1 := args[i];
   --raise notice 'p1=%', v1;
  else 
   --raise notice 'p2=%', v2;
   if v1 = args[1] then return args[i]; end if;
  end if;
 end loop;
 return defval;

end;
$$;

create function tdecode(VARIADIC args text[]) returns text language plpgsql immutable strict as $$
declare
 i int;
 v1 text;
 N int;
 defval text := null;
begin
 --raise notice 'p0=%', args[1];
 N := array_length(args,1);
 if N%2=0 then -- last element represents default value
   defval := args[N];
   --raise notice 'defval = %', defval;
   N := N - 1;
 end if;
 for i in 2..N loop
  if i%2=0 then v1 := args[i];
   --raise notice 'p1=%', v1;
  else
   --raise notice 'p2=%', v2;
   if v1 = args[1] then return args[i]; end if;
  end if;
 end loop;
 return defval;

end;
$$;
~*/
create function decode(VARIADIC args anyarray) returns anyelement language plpgsql immutable as $$
declare
 i int;
 v int;
 N int;
 D int := 0;
begin
 --raise notice 'p0=%', args[1];
 N := array_length(args,1);
 if N%2=0 then -- last element represents default value
   D := N;
   --raise notice 'defval = %', defval;
   N := N - 1;
 end if;
 for i in 2..N loop
  if i%2=0 then v := i;
   --raise notice 'v=%', v;
  else
   --raise notice 'p2=%', v2;
   if args[v] = args[1] then return args[i]; end if;
  end if;
 end loop;
 if D=0 then
  return null;
 else
  return args[D];
 end if;

end;
$$;

create function nvl(val anyelement, defval anyelement) returns anyelement language plpgsql immutable as $$
begin
  if val is null then
    return defval;
  else
    return val;
  end if;
end;
$$;

create function nvl2(val anyelement, not_null_val anyelement, null_val anyelement) returns anyelement language plpgsql immutable as $$
begin
  if val is null then
    return null_val;
  else
    return not_null_val;
  end if;
end;
$$;
