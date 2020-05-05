create function nvl(text, text) returns text as '$libdir/nvl' language C immutable;

--create function sdecode(VARIADIC args text[]) returns text as '$libdir/decode' language C immutable strict;
create function isluhn(num text) returns int as '$libdir/luhn' language C immutable strict;
create function luhnval(num text) returns int as '$libdir/luhn' language C immutable strict;
create function mapcount(tname text) returns int as '$libdir/luhn' language C immutable strict;

create function idecode(VARIADIC args int[]) returns int language plpgsql immutable strict as $$
declare
 i int;
 v1 int;
 v2 int;
begin
 raise notice 'p0=%', args[1];
 for i in 2..array_length(args,1) loop
  if i%2=0 then v1 := args[i];
   raise notice 'p1=%', v1;
  else v2 = args[i]; 
   raise notice 'p2=%', v2;
   if v1 = args[1] then return v2; end if;
  end if;
 end loop;
 return null;

end;
$$;
