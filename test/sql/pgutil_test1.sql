select luhnval('400000000000000'), isluhn('4000000000000002'), isluhn('4000000000000010'), isluhn('4000000000000011');
select decode(''::text,'A','B','C','D'), decode(''::text,'A','B','V','D','?'), decode('A'::text,'A','B','C','D'), decode('C'::text,'A','B','C','D'), decode(null::text,'A','B','C','D');
select nvl(null::text,'A'), nvl('a'::text,'A'), nvl(null::int,0), nvl(123::int,1), nvl2(1::int,1,2), nvl2(null::int,1,2);
