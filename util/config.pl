#!/usr/bin/perl

sub config_makefile {
  my ($src, $dst, $c_objs, $cpp_objs) = @_;
  my $in, $out;
  my @c_objs = @$c_objs;
  my @cpp_objs = @$cpp_objs;
  my $c_objs_str = join(' ', @c_objs);
  my $cpp_objs_str = join(' ', @cpp_objs);
  
  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    print $out $_;
  }
  
  print $out "\r\n# ----- added by config.pl -----\r\n";
  print $out "MOD_COBJS += $c_objs_str\r\n";
  print $out "MOD_CXXOBJS += $cpp_objs_str\r\n\r\n";

  close($in);
  close($out);
}

sub config_cfgfile {
  my ($src, $dst, $c_objs, $cpp_objs) = @_;
  my $in, $out;
  my @c_objs = @$c_objs;
  my @cpp_objs = @$cpp_objs;
  
  if(!open($in, $src)){
    die "can't open file: $src";
  }
  
  if(!open($out, ">$dst")){
    die "can't open file: $dst";
  }
  
  while(<$in>){
    print $out $_;
  }
  
  print $out "\r\n/* ----- added by config.pl ----- */\r\n";
  
  foreach(@c_objs){
    print $out "ATT_MOD(\"$_\");\r\n";
  }
  
  foreach(@cpp_objs){
    print $out "ATT_MOD(\"$_\");\r\n";
  }

  close($in);
  close($out);
}


sub run {
  my $dir = $ARGV[0];
  my $c_objs = $ARGV[1];
  my $cpp_objs = $ARGV[2];
  my $makefile = "$dir/Makefile.inc";
  my $cfgfile = "$dir/app.cfg";
  my $makefile_back = "$makefile.bak";
  my $cfgfile_back = "$cfgfile.bak";
  
  my @c_objs = grep $_ ne '', split(/\s+/, $c_objs);
  my @cpp_objs = grep $_ ne '', split(/\s+/, $cpp_objs);
  
  rename $makefile, $makefile_back;
  rename $cfgfile, $cfgfile_back;
  
  config_makefile($makefile_back, $makefile, \@c_objs, \@cpp_objs);
  config_cfgfile($cfgfile_back, $cfgfile, \@c_objs, \@cpp_objs);
}

run();

1;
