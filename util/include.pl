#!/usr/bin/perl

$BASEDIR = $0;
$BASEDIR =~ s/[\/\\]?[^\/\\]+$//;
require "$BASEDIR/functions.pl";

$FILENAME = 'Include.h';
$RULE_PATH = 'rule';
$FILTER_PATH = 'filter';
$SHARE_PATH = 'share';

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

sub run {
  my $tempdir = $ARGV[0];
  my $srcdir = $ARGV[1];

  my @rule_list = read_dir("$srcdir/$RULE_PATH", '.h');
  my @filter_list = read_dir("$srcdir/$FILTER_PATH", '.h');
  my @share_list = read_dir("$srcdir/$SHARE_PATH", '.h');

  my $rule_include = get_include_text($RULE_PATH, \@rule_list);
  my $filter_include = get_include_text($FILTER_PATH, \@filter_list);
  my $share_include = get_include_text($SHARE_PATH, \@share_list);

  my %map = (
    'RULE_INCLUDE' => $rule_include,
    'FILTER_INCLUDE' => $filter_include,
    'SHARE_INCLUDE' => $share_include,
  );

  template("$tempdir/$FILENAME.temp", "$srcdir/$FILENAME", \%map);
}

run();

1;
