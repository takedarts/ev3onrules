#!/usr/bin/perl

sub run {
  my $file = $ARGV[0];
  my $srcs = $ARGV[1];
  my $objs = '';
  
  if(-e $file){
    my $in;
  
    if(!open($in, $file)){
      die "can not open file: $file";
    }
    
    $objs = <$in>;
    close($in);
  }
  
  $srcs =~ s/^\s+//;
  $srcs =~ s/\s+$//;
  $objs =~ s/^\s+//;
  $objs =~ s/\s+$//;
  
  if($srcs ne $objs){
    if(!open($out, ">$file")){
      die "can not open file: $file";
    }
    
    print $out $srcs;
    close($out);
  }
}

run();

1;
