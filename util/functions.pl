#!/usr/bin/perl

sub template {
  my ($src, $dst, $map) = @_;
  my %map = %$map;
  my $keys = join('|', map { quotemeta } keys %map);
  my $in, $out;

  if(!open($in, $src)){
    die "can not open file: $src";
  }

  if(!open($out, ">$dst")){
    die "can not open file: $dst";
  }

  while(<$in>){
    ~s/{\$($keys)}/$map{$1}/eg;
    print $out $_;
  }

  close($in);
  close($out)
}

sub read_dir {
  my ($dir, $suffix) = @_;
  my $handle;
  my @files;
  my $include = '';
  my $create = '';

  if(!opendir($handle, $dir)){
    die("can not open dir: $dir");
  }

  foreach(readdir($handle)){
    if(/$suffix$/){
      push(@files, $_);
    }
  }

  closedir($handle);

  return @files;
}

1;
