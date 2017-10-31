package in.ac.iitk.cse.cs252.transactions;

import org.bitcoinj.core.NetworkParameters;
import org.bitcoinj.core.Transaction;
import org.bitcoinj.core.Utils;
import org.bitcoinj.script.Script;
import org.bitcoinj.script.ScriptBuilder;

import java.io.File;
import java.math.BigInteger;
import java.net.UnknownHostException;

import static org.bitcoinj.script.ScriptOpCodes.*;

/**
 * Created by bbuenz on 24.09.15.
 */
public class LinearEquationTransaction extends ScriptTransaction {
    ECKey key = randKey();
    // TODO: Problem 2
    public LinearEquationTransaction(NetworkParameters parameters, File file, String password) {
        super(parameters, file, password);
    }

    @Override
    public Script createInputScript() {
            ScriptBuilder builder = new ScriptBuilder();
            builder.op(OP_2DUP).op(OP_SUB).op(OP_ABS).data(150).op(OP_EQUALVERIFY).op(OP_ADD).data(792).op(OP_EQUALVERIFY).op(OP_CHECKSIG);
            return builder.build();
    }

    @Override
    public Script createRedemptionScript(Transaction unsignedScript) {
            TransactionSignature txSig = sign(unsignedScript, key);        
            ScriptBuilder builder = new ScriptBuilder();
            builder.data(471);
            builder.data(-321);
            builder.data(txSig.encodeToBitcoin());
            builder.data(key.getPubKey());
            return builder.build();
    }

    private byte[] encode(BigInteger bigInteger) {
        return Utils.reverseBytes(Utils.encodeMPI(bigInteger, false));
    }
}
