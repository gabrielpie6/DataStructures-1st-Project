'''
Created on 1 de out. de 2021

@author: evand
'''

'''
Created on 5 de abr de 2019

@author: Evandro
'''

#from datetime import date
from datetime import datetime
#import datetime
import getopt
import glob
import os
#import re
#import shutil
import subprocess
import sys
import zipfile


abrir = True    # -z muda para False
compilar = True # -c muda para False
testar = True   # -t muda para False
sohUmAluno = False
pastaAluno = "COMPILACAO"
nomeExec = "t1"

logfile = "saida-"+pastaAluno+".txt"
logexec = ""
extTstFile=".geo"
lf = sys.stdout

def reportFileList(arqs,titulo):
    print("\n>>\n>> %s\n>>\n"%titulo)
    print("Numero de arquivos: %d" % len(arqs))
    totSize = 0
    for arq in arqs:
        _,barq = os.path.split(arq)
        size = os.stat(arq).st_size
        totSize += size
        print(" {:.<30} {}".format(barq,size))
    print(":::%d\n" % totSize)
        
def filesContent(arqs,titulo,minSize = 100):
    print("\n>>\n>> %s\n>>\n"%titulo)

    nReported = 0
    for arq in arqs:
        size = os.stat(arq).st_size
        if size < minSize:
            _,barq = os.path.split(arq)
            print(" {:.<30} {}".format(barq,size))
            nReported += 1
    print("Arquivos reportados {}".format(nReported))
        
def relatorio(outdir):
    svgFiles = os.path.join(outdir,"*.svg")
    #print(svgFiles)
    arqs_svg =  glob.glob(svgFiles)
    arqs_svg.sort()

    txtFiles = os.path.join(outdir,"*.txt")
    arqs_txt =  glob.glob(txtFiles)
    arqs_txt.sort()

    reportFileList(arqs_svg,"Arquivos SVG produzidos")
    reportFileList(arqs_txt,"Arquivos TXT produzidos");
    
    filesContent(arqs_svg,"Arquivos SVG pequenos",30)
    filesContent(arqs_txt,"Arquivos TXT pequenos",5);
    
def logNow():
    print(".[" + datetime.now().isoformat()+"].")
    lf.flush()
    sys.stdout.flush()
    sys.stderr.flush()

def preparaDirs():
    os.mkdir("alunos")
    os.mkdir("t")
    os.mkdir("zip")
           
def runTeste(cmd):
    print (">> " + cmd + "\n")
    lf.flush()
    logNow()
    try:
        subprocess.call(cmd, stdout=lf, stderr=lf, shell=True)
    except OSError as ose:
        print("ERRO AO TENTAR EXECUTAR PROGRAMA: ",ose)
    except KeyboardInterrupt:
        print("***Teste interrompido")
        logNow()
        print("\n")
    lf.flush()

def formataComando(dir_tst, dir_saida, prog,arq, extraArgs="",ecpm=True,comVias=True,comBd=True,criarBd=True, 
                   nomebd=""): 
    path,barq = os.path.split(arq)
    nomearq,_ = os.path.splitext(barq)
    bed = " -e %s" % (dir_tst)   
    bsd = " -o %s" % (dir_saida)

    if ecpm:
        ecpmStr = " -ec %s.ec -pm %s.pm" % (nomearq,nomearq)
    else:
        ecpmStr = ""

    if comVias:
        viasStr = " -v %s-v.via" % nomearq
    else: 
        viasStr = ""
        
    if comBd:
        if criarBd:
            bdStr = "-k %s" % (nomebd) 
        else:
            bdStr = "-u %s" % (nomebd)
    else:
        bdStr = ""
        
    lnc = "%s %s %s %s -f %s %s %s %s" % (prog,extraArgs,bed,bsd,barq,ecpmStr,viasStr,bdStr)

    return (lnc,path,nomearq)
    
def execTeste(dir_tst, dir_saida, prog, arqgeo, extraPars="",ecpm=False,comVias=False, comBd=False):
    print("===== EXECUTANDO TESTES: ")
    print("    > dir_tst:" + dir_tst);
    print("    > dir saida: " + dir_saida)
    print("    > prog: " + prog)
    print("    > arqgeo: " + arqgeo)
    print("    > ecpm: " + str(ecpm))
    print("    > comVias: " + str(comVias))
    print("    > comBd: " + str(comBd))

    removeArquivosDir(dir_saida,"*.txt")
    removeArquivosDir(dir_saida,"*.svg")
    arq_input_ptrn = os.path.join(dir_tst,arqgeo)#+ extTstFile
#    bed = "-e %s" % (dir_tst)
    
    arqs_geo =  glob.glob(arq_input_ptrn)
    arqs_geo.sort()

#    totGeos = len(arqs_geo)
    numGeoProcessados = 0
    
    if len(arqs_geo) == 0:
        print("   erro: Nenhum arquivo .geo encontrado")
        
    for arq in arqs_geo:
        print("   > arq =  " + arq)
        numGeoProcessados += 1
        
        (lnc,path,nomearq) = formataComando(dir_tst, dir_saida, prog,arq,extraPars,ecpm,False,False,False)

        runTeste(lnc)
        print("   > nomearq: %s \n" % (nomearq))
        dirqry = os.path.join(path,nomearq)

        if os.path.isdir(dirqry):
            # existem arquivos de consulta associados ao .geo corrente
            
            (lnc,path,nomearq) = formataComando(dir_tst, dir_saida, prog,arq, extraPars,ecpm,comVias,False,False)
            qry_ptrn = os.path.join(dirqry,"*.qry")
            arqs_qry = glob.glob(qry_ptrn)
            print("   dirqry: %s  qry_ptrn: %s  #qrys: %d " % (dirqry,qry_ptrn,len(arqs_qry)))
            
            acabou = False
            qryIt = iter(arqs_qry)
            nextQry = qryIt.__next__()
             
            while not acabou:    #for qry in arqs_qry:
                qry = nextQry
                try:
                    nextQry = qryIt.__next__()
                except StopIteration:
                    acabou = True                        
                    
                _,bqry = os.path.split(qry)
                qryf = os.path.join(nomearq,bqry)
                lncqry = "%s -q %s" % (lnc,qryf)
                runTeste(lncqry)
        


#
# Descomprime o zip no diretorio de testes
#
def abreZip(dest_dir,zip_dir, zip_file,subdirs=[]):
    global dirAlunoLeiame
    os.chdir(zip_dir)
    with zipfile.ZipFile(zip_file,'r') as zf:
        zf.testzip()
        nomeDirDef,_ = os.path.splitext(zip_file)
        daln = nomeDirDef
        dir_aluno = os.path.join(dest_dir,daln)
        os.mkdir(dir_aluno)
           
        print("##\n## Criado diretorio: " + dir_aluno + "\n##")
        print("  > extraindo zip para diretorio de testes")
        zf.extractall(dir_aluno)
        # criando diretorios de saida
        # no futuro substituir por os.makedirs(name, mode=Oo777, exist_ok=False)
        dir_aluno_o = os.path.join(dir_aluno,"o")
        os.mkdir(dir_aluno_o)
        
        for d in subdirs:
            sd = os.path.join(dir_aluno_o,d)
            os.mkdir(sd)
            
        return dir_aluno

def compila(executavel="t1"):
    print("  > compilando")
    logNow()
    mkc="make %s" % executavel
    subprocess.call(mkc, stdout=lf, stderr=lf, shell=True)
    logNow()

def removeArquivosDir(dr,padrao):
    try:
        cwd = os.getcwd()
        os.chdir(dr)
        print("   > removendo arquivos  pre-existentes: %s  %s \n" % (dr,padrao))
        arqsrm = glob.glob(padrao)
        for arqrm in arqsrm:
            os.remove(arqrm)
    except OSError as ose:
        print("ERRO NO DIRETORIO src: ",ose)
    finally:
        os.chdir(cwd)
        
    
def compilaSubmissao(aluno_d):
    cwd = os.getcwd()
    try:
        print("## COMPILANDO SUBMISSAO DO ALUNO: " + aluno_d)
        os.chdir(aluno_d)
        print("   > removendo .o pre-existentes ")
        arqso = glob.glob("*.o")
        for arqo in arqso:
            os.remove(arqo)
    except OSError as ose:
        print("ERRO NO DIRETORIO src: ",ose)

    lf.flush()
    compila(nomeExec)
    lf.flush()
    os.chdir(cwd)
    

# inicio contem, se aplicavel, um argumento para a primeira
# invocacao do programa
def testaSubmissao(aluno_d,testes_dir, arqgeo, extraPars="", ecpm=False,comVias=False, comBd=False):
    adir_o = os.path.join(aluno_d,"o")
    adir_ot6 = os.path.join(aluno_d,"src",nomeExec)
    execTeste(testes_dir, adir_o,    adir_ot6, arqgeo, extraPars,ecpm,comVias, comBd)
    relatorio(adir_o)
    sys.stdout.flush()
    sys.stderr.flush()


def abreZips(arqs,zip_dir,home_dir,alunosd="alunos",subdirs=[]):
    dirs_abertos = []
    cwd = os.getcwd()
    for a in arqs:
        os.chdir(home_dir)
        dir_alunos = os.path.join(home_dir,alunosd)
        try:
            print("> extraindo zip: " + a)
            dir_aluno = abreZip(dir_alunos,zip_dir,a,subdirs)
            dirs_abertos.append(dir_aluno)
            os.chdir(dir_aluno)
            os.system("chmod 700 -R *" + logexec)
        except zipfile.BadZipfile as bzf:
            print("ERRO AO ABRIR ZIP: ",bzf)
        except KeyError as ke:
            print("ERRO AO ABRIR ZIP: ",ke)
    lf.flush()
    os.chdir(cwd)
    return  dir_alunos


def processaTodosZip(zip_d,teste_d,home_d,arqgeo,alunosd="alunos",extraPars="",ecpm=False,comVias=False, comBd=False,subdirs=[]):
    global abrir,sohUmAluno,compilar,testar
    os.chdir(zip_d)
    arqs = glob.glob("*")
    arqs.sort() 

    # Abrindo zips
    if abrir:
        print("##\n## ABRINDO OS ZIPS SUBMETIDOS\n##\n\n")
        sys.stdout.flush()
        sys.stderr.flush()
        abreZips(arqs,zip_d,home_d,alunosd,subdirs)

    alunos_d = os.path.join(home_d,alunosd)
    os.chdir(alunos_d)

    arqs=[pastaAluno]
    
    saluno = arqs[0]

    # Compilacao
    if compilar:
        print  ("====> COMPILANDO: " + saluno + "\n")
        lf.flush()
        sys.stdout.flush()
        sys.stderr.flush()
        compilaSubmissao(os.path.join(alunos_d,saluno,"src"))

    if testar:
        os.chdir(home_d)
        print("====> TESTANDO: " + saluno + "\n")
        lf.flush()
        sys.stdout.flush()
        sys.stderr.flush()
        testaSubmissao(os.path.join(alunos_d,saluno),teste_d,arqgeo,extraPars,ecpm,comVias, comBd)
        

def uso():
    print ('Exemplos de invocacoes tipicas: ')
    print ('   * compilar e testar (diretorio aluno): python3 et.py -z -p [dir]')
    print ('   * unzipar todos .zip:   python3 ct.py -Z -c -t')

def executa():
    global abrir,sohUmAluno,compilar,testar,pastaAluno,nomeExec,lf,execExtras
    
    ecpm=False
    comVias=False
    comBd=False
    subdirs=[]
    
    print("Executando")
    nomeAluno = ""
    extraPars = ""  
    arqgeo = "a.geo"
    try:
        opts, _ = getopt.getopt(sys.argv[1:], "zZcthp:IE:X:g:mv", [])
        for opt, arg in opts:
            if opt == '-h':
                uso()
                sys.exit()
            elif opt in ("-I"):
                preparaDirs()
                sys.exit()
            elif opt in ("-p"):
                nomeAluno = arg  # nome do arquivo zip (sem extensao)
            elif opt in ("-E"):
                nomeExec = arg  # nome do executavel  
            elif opt in ("-X"):
                extraPars = arg  # parametro para indicar primeira em bateria de testes
            elif opt in ("-z"):
                abrir = False
            elif opt in ("-Z"):  # unzipa todos os arquivos .zip dentro do diretorio zip
                dirAlunoLeiame = False   
            elif opt in ("-m"):
                ecpm = True
            elif opt in ("-v"):  # unzipa todos os arquivos .zip dentro do diretorio zip
                comVias = True   
            elif opt in ("-c"):
                compilar = False
            elif opt in ("-t"):
                testar = False
            elif opt in ("-g"):
                arqgeo = arg
    except getopt.GetoptError:
        uso()
        sys.exit(2)

    print("#######\n## EXECUCAO INICIADA:  %s\n#################\n\n" % arqgeo)
    logNow()
    pastaAluno =  nomeAluno 
    logfile = "saida-" +pastaAluno+".txt"

    home_dir = os.getcwd()
    zip_d = os.path.join(home_dir,"zip")
    teste_d = os.path.join(home_dir,"t")
    alunosd = "alunos"
          
    lf = open(logfile, 'w')    
    sys.stdout = lf;
    sys.stderr = lf;

    try:
        processaTodosZip(zip_d,teste_d,home_dir,arqgeo,alunosd,extraPars,ecpm,comVias, comBd,subdirs)
    except KeyboardInterrupt:
        print("Script interrompido")
        logNow()
    print("================================\n")


executa()



# colocar et.py em algum diretorio (melhor vazio)
# 
# 
# executar: python et.py -I
#    - serao criados tres diretorios: t, alunos, zips
#     - obs: talvez seja necessario executar python3 em vez de python
# 
# 
# colocar os casos de testes (*.geo e subdiretorios com *.qry) dentro do diretorio t
# colocar o zip que vc ira submeter dentro de zips (ex: jmsilva.zip)
# 
# 
# executar: python et.py -Z -c -t
#    - o arquivo .zip (que esta' dentro de zips) e' inflado em alunos dentro de um 
#       subdiretorio com o mesmo nome do zip (exemplo: jmsilva)
#    - dentro do subdiretorio e' criado um diretorio o.
#   
#    
# para executar um .geo (exemplo: t1.geo) e os respectivos qry para um aluno especifico (exemplo: jmsilva):  
#       python et.py -z -p jmsilva  -g tst1.geo
# 
# 
#    - sera invocado o make (exemplo: makefile  o makefile deve estar em alunos/jmsilva/src)
#    - os arquivos svg e txt sao colocados no diretorio o (no exemplo: alunos/jmsilva/o)
#    - sera produzido um arquivo com o relatorio de saida (exemplo: saida-jmsilva.txt)
#
# se o nome do executavel for diferente de t1, usar -E <nome> para informar o nome do executavel
#
# se existirem arquivos de pessoas e estabelecimentos comerciais, usar -m
#
# se existirem arquivos de vias, usar -v

