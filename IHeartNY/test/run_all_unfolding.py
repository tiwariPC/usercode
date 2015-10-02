import subprocess
import sys

from optparse import OptionParser
parser = OptionParser()

parser.add_option('--closureTests', metavar='F', action='store_true',
                  default=False,
                  dest='closureTests',
                  help='Run closure test')

parser.add_option('--genCheck', metavar='F', action='store_true',
                  default=False,
                  dest='genCheck',
                  help='Run generator cross checks')

parser.add_option('--ttbarPDF', metavar='F', type='string', action='store',
                  default='CT10_nom',
                  dest='pdf',
                  help='Which PDF set and nominal vs up/down? Or Q2 up/down?')

parser.add_option('--oneRegion', metavar='F', action='store_true',
                  default=False,
                  dest='oneRegion',
                  help='Unfold only for 1 top-tag, 1 b-tag region')

(options, args) = parser.parse_args()
argv = []


if ((options.pdf == 'CT10_nom' or options.pdf == 'CT10_pdfup' or options.pdf == 'CT10_pdfdown' or 
    options.pdf == 'MSTW_nom' or options.pdf == 'MSTW_pdfup' or options.pdf == 'MSTW_pdfdown' or 
    options.pdf == 'NNPDF_nom' or options.pdf == 'NNPDF_pdfup' or options.pdf == 'NNPDF_pdfdown' or 
    options.pdf == 'scaleup' or options.pdf == 'scaledown' or
    options.pdf == 'MG' or options.pdf == 'mcnlo') == False):
    print "Invalid option for --ttbarPDF! exiting..."
    sys.exit()


if options.closureTests:
    path = [
        ## closure tests
        "python unfoldTopPt.py --closureTest --addNoBtag",
        "python unfoldTopPt.py --closureTest --addNoBtag --lepType=ele",
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep",
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep --lepType=ele",
    ]
elif options.genCheck:
    path = [
        ## checks using different MC generators
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep --ttbarPDF=MG --whatClosure=reverse",
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep --lepType=ele --ttbarPDF=MG --whatClosure=reverse",
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep --ttbarPDF=mcnlo --whatClosure=reverse",
        "python unfoldTopPt.py --closureTest --addNoBtag --twoStep --lepType=ele --ttbarPDF=mcnlo --whatClosure=reverse",
        "python unfoldTopPt.py --closureTest --addNoBtag --ttbarPDF=mcnlo --whatClosure=reverse",
        "python unfoldTopPt.py --closureTest --addNoBtag --lepType=ele --ttbarPDF=mcnlo --whatClosure=reverse",
    ]
elif options.pdf == "CT10_nom" and not options.oneRegion: #run all alternatives for CT10 nominal
    path = [
        ## unfolding, combining the 1 top-tag, 1 b-tag and 1 top-tag, 0 b-tag regions
        "python unfoldTopPt.py --addNoBtag --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --lepType=ele --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --addNoBtag --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --addNoBtag --twoStep --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --systVariation=btagdn --ttbarPDF="+options.pdf,
    ]
elif options.pdf == "CT10_nom": #run all alternatives for CT10 nominal
        path = [
        ## unfolding using 1 top-tag, 1 b-tag region only
        "python unfoldTopPt.py --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --lepType=ele --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --twoStep --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --systVariation=btagdn --ttbarPDF="+options.pdf,
        
        "python unfoldTopPt.py --twoStep --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --bkgSyst=bkgup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --bkgSyst=bkgdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=toptagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=toptagdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=toptagHIGHPTup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=toptagHIGHPTdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=jerup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=jerdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=jecup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=jecdn --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=btagup --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --systVariation=btagdn --ttbarPDF="+options.pdf,
    ]
elif options.oneRegion : #for other PDFs, run only minimal set required
    path = [ 
        "python unfoldTopPt.py --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --twoStep --ttbarPDF="+options.pdf,
    ]
else : #for other PDFs, run only minimal set required
    path = [ 
        "python unfoldTopPt.py --addNoBtag --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --lepType=ele --ttbarPDF="+options.pdf,
        "python unfoldTopPt.py --addNoBtag --twoStep --ttbarPDF="+options.pdf,
    ]

## run actual unfolding
for s in path :
    print s
    subprocess.call( [s, ""], shell=True )
    
    
