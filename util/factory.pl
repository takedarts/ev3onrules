#!/usr/bin/perl

$BASEDIR = $0;
$BASEDIR =~ s/[\/\\]?[^\/\\]+$//;
require "$BASEDIR/functions.pl";

$FILENAME = 'Factory.cpp';
$RULE_PATH = 'rule';
$FILTER_PATH = 'filter';
$RULE_SUFFIX = 'Rule';
$FILTER_SUFFIX = 'Filter';

sub get_include_text {
  my ($path, $list) = @_;
  my @list = @$list;
  my $text = '';

  foreach(@list){
    $text .= "#include \"$path/$_\"\r\n";
  }

  $text =~ s/[\s]+$//;
  $text =~ s/^[\s]+//;

  return $text;
}

sub get_create_text {
  my ($path, $list) = @_;
  my @list = @$list;
  my $text = '';

  foreach(@list){
    ~ s/\.h$//;
    $text .= "  list.push_back(new $_());\r\n";
  }

  $text =~ s/[\s]+$//;
  $text =~ s/^[\s]+//;

  return $text;
}

sub run {
  my $tempdir = $ARGV[0];
  my $srcdir = $ARGV[1];

  my @rule_list = read_dir("$srcdir/$RULE_PATH", $RULE_SUFFIX . '.h');
  my $rule_include = get_include_text($RULE_PATH, \@rule_list);
  my $rule_create = get_create_text($RULE_PATH, \@rule_list);
  my @filter_list = read_dir("$srcdir/$FILTER_PATH", $FILTER_SUFFIX . '.h');
  my $filter_include = get_include_text($FILTER_PATH, \@filter_list);
  my $filter_create = get_create_text($FILTER_PATH, \@filter_list);

  my %map = (
    'RULE_INCLUDE' => $rule_include,
    'RULE_CREATE' => $rule_create,
    'FILTER_INCLUDE' => $filter_include,
    'FILTER_CREATE' => $filter_create,
  );

  template("$tempdir/$FILENAME.temp", "$srcdir/$FILENAME", \%map);
}

run();

1;
